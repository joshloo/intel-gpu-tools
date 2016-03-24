/*
 * Plane blending feature test program
 * Copyright 2016 Intel Corporation
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Josh Loo <tung.lun.loo@intel.com>
 */

/*
 * This test program is to exercise plane blending API 
 */
 
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include <xf86drmMode.h>

#include "igt.h"
#include "igt_aux.h"

#include "xf86drm.h"
#include "xf86drmMode.h"
#include "drm_fourcc.h"

enum connector_properties {
	CONNECTOR_CRTC_ID = 0,
	NUM_CONNECTOR_PROPS
};

static const char *connector_prop_names[NUM_CONNECTOR_PROPS] = {
	"CRTC_ID"
};

enum crtc_properties {
	CRTC_MODE_ID = 0,
	CRTC_ACTIVE,
	CRTC_BACKGROUND_COLOR,
	NUM_CRTC_PROPS
};

static const char *crtc_prop_names[NUM_CRTC_PROPS] = {
	"MODE_ID",
	"ACTIVE",
	"background_color"
};

enum plane_properties {
	PLANE_SRC_X = 0,
	PLANE_SRC_Y,
	PLANE_SRC_W,
	PLANE_SRC_H,
	PLANE_CRTC_X,
	PLANE_CRTC_Y,
	PLANE_CRTC_W,
	PLANE_CRTC_H,
	PLANE_FB_ID,
	PLANE_CRTC_ID,
	PLANE_TYPE,
	NUM_PLANE_PROPS
};

static const char *plane_prop_names[NUM_PLANE_PROPS] = {
	"SRC_X",
	"SRC_Y",
	"SRC_W",
	"SRC_H",
	"CRTC_X",
	"CRTC_Y",
	"CRTC_W",
	"CRTC_H",
	"FB_ID",
	"CRTC_ID",
	"type"
};

enum plane_type {
	PLANE_TYPE_PRIMARY = 0,
	PLANE_TYPE_OVERLAY,
	PLANE_TYPE_CURSOR,
	NUM_PLANE_TYPE_PROPS
};

static const char *plane_type_prop_names[NUM_PLANE_TYPE_PROPS] = {
	"Primary",
	"Overlay",
	"Cursor"
};


struct kms_atomic_desc {
	int fd;
	uint32_t props_connector[NUM_CONNECTOR_PROPS];
	uint32_t props_crtc[NUM_CRTC_PROPS];
	uint32_t props_plane[NUM_PLANE_PROPS];
	uint64_t props_plane_type[NUM_PLANE_TYPE_PROPS];
};

struct kms_atomic_connector_state {
	struct kms_atomic_state *state;
	uint32_t obj;
	uint32_t crtc_id;
};

struct kms_atomic_plane_state {
	struct kms_atomic_state *state;
	uint32_t obj;
	enum plane_type type;
	uint32_t crtc_mask;
	uint32_t crtc_id; /* 0 to disable */
	uint32_t fb_id; /* 0 to disable */
	uint32_t src_x, src_y, src_w, src_h; /* 16.16 fixed-point */
	uint32_t crtc_x, crtc_y, crtc_w, crtc_h; /* normal integers */
};

struct kms_atomic_blob {
	uint32_t id; /* 0 if not already allocated */
	size_t len;
	void *data;
};

struct kms_atomic_crtc_state {
	struct kms_atomic_state *state;
	uint32_t obj;
	int idx;
	bool active;
	struct kms_atomic_blob mode;
};

struct kms_atomic_state {
	struct kms_atomic_connector_state *connectors;
	int num_connectors;
	struct kms_atomic_crtc_state *crtcs;
	int num_crtcs;
	struct kms_atomic_plane_state *planes;
	int num_planes;
	struct kms_atomic_desc *desc;
};

static void fill_obj_props(int fd, uint32_t id, int type, int num_props,
			   const char **prop_names, uint32_t *prop_ids)
{
	drmModeObjectPropertiesPtr props;
	int i, j;

	props = drmModeObjectGetProperties(fd, id, type);
	igt_assert(props);

	for (i = 0; i < props->count_props; i++) {
		drmModePropertyPtr prop =
			drmModeGetProperty(fd, props->props[i]);

		for (j = 0; j < num_props; j++) {
			if (strcmp(prop->name, prop_names[j]) != 0)
				continue;
			prop_ids[j] = props->props[i];
			break;
		}

		drmModeFreeProperty(prop);
	}

	drmModeFreeObjectProperties(props);
}

static void fill_obj_prop_map(int fd, uint32_t id, int type, const char *name,
			      int num_enums, const char **enum_names,
			      uint64_t *enum_ids)
{
	drmModeObjectPropertiesPtr props;
	int i, j, k;

	props = drmModeObjectGetProperties(fd, id, type);
	igt_assert(props);

	for (i = 0; i < props->count_props; i++) {
		drmModePropertyPtr prop =
			drmModeGetProperty(fd, props->props[i]);

		igt_assert(prop);

		if (strcmp(prop->name, name) != 0) {
			drmModeFreeProperty(prop);
			continue;
		}

		for (j = 0; j < prop->count_enums; j++) {
			struct drm_mode_property_enum *e = &prop->enums[j];

			for (k = 0; k < num_enums; k++) {
				if (strcmp(e->name, enum_names[k]) != 0)
					continue;

				enum_ids[k] = e->value;
				break;
			}
		}

		drmModeFreeProperty(prop);
	}
}

static void
connector_get_current_state(struct kms_atomic_connector_state *connector)
{
	drmModeObjectPropertiesPtr props;
	int i;

	props = drmModeObjectGetProperties(connector->state->desc->fd,
					   connector->obj,
					   DRM_MODE_OBJECT_CONNECTOR);
	igt_assert(props);

	for (i = 0; i < props->count_props; i++) {
		uint32_t *prop_ids = connector->state->desc->props_connector;

		if (props->props[i] == prop_ids[CONNECTOR_CRTC_ID])
			connector->crtc_id = props->prop_values[i];
	}
	drmModeFreeObjectProperties(props);
}

static void crtc_get_current_state(struct kms_atomic_crtc_state *crtc)
{
	drmModeObjectPropertiesPtr props;
	int i;

	props = drmModeObjectGetProperties(crtc->state->desc->fd, crtc->obj,
					   DRM_MODE_OBJECT_CRTC);
	igt_assert(props);

	for (i = 0; i < props->count_props; i++) {
		uint32_t *prop_ids = crtc->state->desc->props_crtc;

		if (props->props[i] == prop_ids[CRTC_MODE_ID]) {
			drmModePropertyBlobPtr blob;

			crtc->mode.id = props->prop_values[i];
			if (!crtc->mode.id) {
				crtc->mode.len = 0;
				continue;
			}

			blob = drmModeGetPropertyBlob(crtc->state->desc->fd,
						      crtc->mode.id);
			igt_assert(blob);
			igt_assert_eq_u32(blob->length,
					  sizeof(struct drm_mode_modeinfo));

			if (!crtc->mode.data ||
			    memcmp(crtc->mode.data, blob->data, blob->length) != 0)
				crtc->mode.data = blob->data;
			crtc->mode.len = blob->length;
		}
		else if (props->props[i] == prop_ids[CRTC_ACTIVE]) {
			crtc->active = props->prop_values[i];
		}
	}

	drmModeFreeObjectProperties(props);
}

static void plane_get_current_state(struct kms_atomic_plane_state *plane)
{
	struct kms_atomic_desc *desc = plane->state->desc;
	drmModeObjectPropertiesPtr props;
	int i;

	props = drmModeObjectGetProperties(desc->fd, plane->obj,
					   DRM_MODE_OBJECT_PLANE);
	igt_assert(props);

	for (i = 0; i < props->count_props; i++) {
		uint32_t *prop_ids = desc->props_plane;

		if (props->props[i] == prop_ids[PLANE_CRTC_ID])
			plane->crtc_id = props->prop_values[i];
		else if (props->props[i] == prop_ids[PLANE_FB_ID])
			plane->fb_id = props->prop_values[i];
		else if (props->props[i] == prop_ids[PLANE_CRTC_X])
			plane->crtc_x = props->prop_values[i];
		else if (props->props[i] == prop_ids[PLANE_CRTC_Y])
			plane->crtc_y = props->prop_values[i];
		else if (props->props[i] == prop_ids[PLANE_CRTC_W])
			plane->crtc_w = props->prop_values[i];
		else if (props->props[i] == prop_ids[PLANE_CRTC_H])
			plane->crtc_h = props->prop_values[i];
		else if (props->props[i] == prop_ids[PLANE_SRC_X])
			plane->src_x = props->prop_values[i];
		else if (props->props[i] == prop_ids[PLANE_SRC_Y])
			plane->src_y = props->prop_values[i];
		else if (props->props[i] == prop_ids[PLANE_SRC_W])
			plane->src_w = props->prop_values[i];
		else if (props->props[i] == prop_ids[PLANE_SRC_H])
			plane->src_h = props->prop_values[i];
		else if (props->props[i] == prop_ids[PLANE_TYPE]) {
			int j;

			for (j = 0; j < ARRAY_SIZE(desc->props_plane_type); j++) {
				if (props->prop_values[i] == desc->props_plane_type[j]) {
					plane->type = j;
					break;
				}
			}
		}
	}

	drmModeFreeObjectProperties(props);
}

static uint32_t blob_duplicate(int fd, uint32_t id_orig)
{
	drmModePropertyBlobPtr orig = drmModeGetPropertyBlob(fd, id_orig);
	uint32_t id_new;

	igt_assert(orig);
	do_or_die(drmModeCreatePropertyBlob(fd, orig->data, orig->length,
					    &id_new));
	drmModeFreePropertyBlob(orig);

	return id_new;
}

static void atomic_state_free(struct kms_atomic_state *state)
{
	free(state->crtcs);
	free(state->planes);
	free(state->connectors);
	free(state);
}

static void atomic_setup(struct kms_atomic_state *state)
{
	struct kms_atomic_desc *desc = state->desc;
	drmModeResPtr res;
	drmModePlaneResPtr res_plane;
	drmModeConnectorPtr connector;

	desc->fd = drm_open_driver_master(DRIVER_INTEL);
	igt_assert_fd(desc->fd);

	do_or_die(drmSetClientCap(desc->fd, DRM_CLIENT_CAP_ATOMIC, 1));

	res = drmModeGetResources(desc->fd);
	res_plane = drmModeGetPlaneResources(desc->fd);
	igt_assert(res);
	igt_assert(res_plane);

	igt_assert_lt(0, res->count_crtcs);
	state->num_crtcs = res->count_crtcs;
	state->crtcs = calloc(state->num_crtcs, sizeof(*state->crtcs));
	igt_assert(state->crtcs);

	igt_assert_lt(0, res_plane->count_planes);
	state->num_planes = res_plane->count_planes;
	state->planes = calloc(state->num_planes, sizeof(*state->planes));
	igt_assert(state->planes);

	igt_assert_lt(0, res->count_connectors);
	state->num_connectors = res->count_connectors;
	state->connectors = calloc(state->num_connectors,
				   sizeof(*state->connectors));
	igt_assert(state->connectors);

	fill_obj_props(desc->fd, res->crtcs[0],
		       DRM_MODE_OBJECT_CRTC, NUM_CRTC_PROPS,
		       crtc_prop_names, desc->props_crtc);

	fill_obj_props(desc->fd, res_plane->planes[0],
		       DRM_MODE_OBJECT_PLANE, NUM_PLANE_PROPS,
		       plane_prop_names, desc->props_plane);
			   
	fill_obj_prop_map(desc->fd, res_plane->planes[0],
			  DRM_MODE_OBJECT_PLANE, "type",
			  NUM_PLANE_TYPE_PROPS, plane_type_prop_names,
			  desc->props_plane_type);

	fill_obj_props(desc->fd, res->connectors[0],
		       DRM_MODE_OBJECT_CONNECTOR, NUM_CONNECTOR_PROPS,
		       connector_prop_names, desc->props_connector);

	for (int i = 0; i < state->num_crtcs; i++) {
		struct kms_atomic_crtc_state *crtc = &state->crtcs[i];

		crtc->state = state;
		crtc->obj = res->crtcs[i];
		crtc->idx = i;
		crtc_get_current_state(crtc);

		/* The blob pointed to by MODE_ID could well be transient,
		 * and lose its last reference as we switch away from it.
		 * Duplicate the blob here so we have a reference we know we
		 * own. */
		if (crtc->mode.id != 0)
		    crtc->mode.id = blob_duplicate(desc->fd, crtc->mode.id);
	}

	for (int i = 0; i < state->num_planes; i++) {
		drmModePlanePtr plane =
			drmModeGetPlane(desc->fd, res_plane->planes[i]);
		igt_assert(plane);

		state->planes[i].state = state;
		state->planes[i].obj = res_plane->planes[i];
		state->planes[i].crtc_mask = plane->possible_crtcs;
		plane_get_current_state(&state->planes[i]);
	}

	for (int i = 0; i < state->num_connectors; i++) {
		state->connectors[i].state = state;
		state->connectors[i].obj = res->connectors[i];
		connector_get_current_state(&state->connectors[i]);

		connector = drmModeGetConnector(desc->fd, res->connectors[i]);
		if (connector->count_modes > 0){
			printf("%d supported modes detected.\n",connector->count_modes);
		}
	}	

	drmModeFreePlaneResources(res_plane);
	drmModeFreeResources(res);
}

static void run_blendfunc(struct kms_atomic_state *state){
	int alpha = 0;
	uint32_t fb_id;	
	struct igt_fb fb;
	
	for (int i=0; i < state->num_crtcs; i++){
		if (state->crtcs->active){
			printf("CRTC id: %d\n", state->crtcs->mode.id);	
			for (int i = 0; i < 3; i++){
				printf("-- Test %d with overlay alpha %d --\n",i, alpha);
				for (int j=0; j < state->num_planes ;j++){
					if(strcmp(plane_type_prop_names[state->planes[j].type], "Overlay") == 0){
						// Set blend function for XRGB
						printf("Overlay plane id: %d \n", state->planes[j].obj);
						
						// Set blend func to XRGB
						igt_assert_eq(0, drmModeObjectSetProperty(state->desc->fd, state->planes[j].obj, DRM_MODE_OBJECT_PLANE, 18, DRM_BLEND_FUNC(ONE,ZERO)));
						
						// Set framebuffer
						fb_id = igt_create_color_fb(state->desc->fd,500, 500,
													DRM_FORMAT_XRGB8888,
													LOCAL_DRM_FORMAT_MOD_NONE,
													0.0, 1.0, 0.0,
													&fb);
						
						//igt_assert_eq(0, drmModeSetPlane(state->desc->fd, state->planes[j].obj, state->crtcs->mode.id, fb_id, 0, ));
						
						// Set blend color to half opaque green
						igt_assert_eq(0, drmModeObjectSetProperty(state->desc->fd, state->planes[j].obj, DRM_MODE_OBJECT_PLANE, 19, drmModeRGBA(8,0,128,0,alpha))); 
						
						// Set blend func to constant alpha
						igt_assert_eq(0, drmModeObjectSetProperty(state->desc->fd, state->planes[j].obj, DRM_MODE_OBJECT_PLANE, 18, DRM_BLEND_FUNC(CONSTANT_ALPHA,ONE_MINUS_CONSTANT_ALPHA)));
					}
				}
				alpha = alpha + 128;
			}			
		}
	}
	
}

igt_main
{	
	struct kms_atomic_desc desc;
	struct kms_atomic_state *current;
	
	memset(&desc, 0, sizeof(desc));
	current = calloc(1, sizeof(*current));
	igt_assert(current);
	current->desc = &desc;
	
	igt_display_t display;
	
	igt_skip_on_simulation();
	
	igt_fixture
		atomic_setup(current);
		
	igt_subtest("Printing") {		
		printf("Connectors: %d\n",current->num_connectors);
		printf("Planes: %d\n",current->num_planes);
		for (int i=0; i < current->num_planes; i++){
			printf("Plane types: %s\n", plane_type_prop_names[current->planes[i].type]);
		}
		printf("Crtcs: %d\n",current->num_crtcs);
		for (int i=0; i < current->num_crtcs; i++){
			printf("CRTC id: %d\n", current->crtcs->mode.id);
		}
	}
	
	igt_subtest("BlendFunc-Test") {
		run_blendfunc(current);
	}
	
	atomic_state_free(current);
	
	igt_fixture
		close(desc.fd);
		
}
