/*
 * QEMU CXL Support
 *
 * Copyright (c) 2020 Intel
 *
 * This work is licensed under the terms of the GNU GPL, version 2. See the
 * COPYING file in the top-level directory.
 */

#ifndef CXL_H
#define CXL_H


#include "qapi/qapi-types-machine.h"
#include "hw/pci/pci_bridge.h"
#include "hw/pci/pci_host.h"
#include "cxl_pci.h"
#include "cxl_component.h"
#include "cxl_device.h"

#define CXL_COMPONENT_REG_BAR_IDX 0
#define CXL_DEVICE_REG_BAR_IDX 2

#define CXL_WINDOW_MAX 10

typedef struct CXLFixedWindow {
    uint64_t size;
    char **targets;
    struct PXBDev *target_hbs[8];
    uint8_t num_targets;
    uint8_t enc_int_ways;
    uint8_t enc_int_gran;
    /* Todo: XOR based interleaving */
    MemoryRegion mr;
    hwaddr base;
} CXLFixedWindow;

typedef struct CXLState {
    bool is_enabled;
    MemoryRegion host_mr;
    unsigned int next_mr_idx;
    GList *fixed_windows;
} CXLState;

struct CXLHost {
    PCIHostState parent_obj;

    CXLComponentState cxl_cstate;
};

#define TYPE_PXB_CXL_HOST "pxb-cxl-host"
OBJECT_DECLARE_SIMPLE_TYPE(CXLHost, PXB_CXL_HOST)

void cxl_fixed_memory_window_config(MachineState *ms,
                                    CXLFixedMemoryWindowOptions *object,
                                    Error **errp);
void cxl_fixed_memory_window_link_targets(Error **errp);

extern const MemoryRegionOps cfmws_ops;

#endif
