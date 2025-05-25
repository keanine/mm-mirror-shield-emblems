#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "segment_symbols.h"
#include "texture_data.h"
#include "gCustomMirrorShieldDL.h"
#include "gGiCustomMirrorShieldDL.h"
#include "CustomMirrorShieldRayDecal.h"
#include "ArtworkCustomMirrorShield.h"

DECLARE_ROM_SEGMENT(object_link_child);
DECLARE_ROM_SEGMENT(object_mir_ray);
DECLARE_ROM_SEGMENT(icon_item_static_yar);
DECLARE_ROM_SEGMENT(object_gi_shield_3);

extern Gfx* gPlayerShields[];
extern Gfx gLinkHumanMirrorShieldDL[];
extern Mtx gLinkHumanMirrorShieldMtx;
extern Gfx object_mir_ray_DL_0004B0[];
extern Gfx gGiMirrorShieldDL[];

enum MirrorShieldDesigns {
    MIRROR_SHIELD_DESIGN_FACE,
    MIRROR_SHIELD_DESIGN_BASIC,
    MIRROR_SHIELD_DESIGN_IKANA,
    MIRROR_SHIELD_DESIGN_CRESCENT,
    MIRROR_SHIELD_DESIGN_GERUDO,
};

enum MirrorShieldGeo {
    MIRROR_SHIELD_GEO_VANILLA,
    MIRROR_SHIELD_GEO_ARTWORK,
};

void* gRam;
uintptr_t gVrom;
size_t gSize;
RECOMP_HOOK("DmaMgr_ProcessRequest") void on_DmaMgr_RequestSync(DmaRequest* req) {
    gRam = req->dramAddr;
    gVrom = req->vromAddr;
    gSize = req->size;
}

// Replace Models
RECOMP_HOOK_RETURN("DmaMgr_ProcessRequest") void after_dma() {
    if (gVrom == SEGMENT_ROM_START(object_link_child)) {
        uintptr_t old_segment_6 = gSegments[0x06];
        gSegments[0x06] = OS_K0_TO_PHYSICAL(gRam);
        Gfx* to_patch = Lib_SegmentedToVirtual(gLinkHumanMirrorShieldDL);
        switch (recomp_get_config_u32("mirror_shield_geo"))
        {
        case MIRROR_SHIELD_GEO_VANILLA:
        gSPBranchList(to_patch , gCustomMirrorShieldDL);
            break;
        case MIRROR_SHIELD_GEO_ARTWORK:
        gSPBranchList(to_patch , ArtworkCustomMirrorShield);
            break;
        }
        gSegments[0x06] = old_segment_6;
    }
    if (gVrom == SEGMENT_ROM_START(object_mir_ray)) {
        uintptr_t old_segment_6 = gSegments[0x06];
        gSegments[0x06] = OS_K0_TO_PHYSICAL(gRam);
        Gfx* to_patch = Lib_SegmentedToVirtual(object_mir_ray_DL_0004B0);
        gSPBranchList(to_patch , CustomMirrorShieldRayDecal);
        gSegments[0x06] = old_segment_6;
    }
    if (gVrom == SEGMENT_ROM_START(object_gi_shield_3)) {
        uintptr_t old_segment_6 = gSegments[0x06];
        gSegments[0x06] = OS_K0_TO_PHYSICAL(gRam);
        Gfx* to_patch = (Gfx*)Lib_SegmentedToVirtual(gGiMirrorShieldDL);
        gSPBranchList(to_patch , gGiCustomMirrorShieldDL);
        gSegments[0x06] = old_segment_6;
    }
    gVrom = 0;
    gRam = NULL;
}

extern u64 gItemIconMirrorShieldTex[];
u8 gCurIconIsMirrorShield = 0;
PlayState* gPlayState;
u8 gId;
void* gDst;
u8 gAlreadyTranslated = 0;
uintptr_t gTranslatedAddress;
RECOMP_HOOK("CmpDma_LoadFileImpl") void on_CmpDma_LoadFileImpl(uintptr_t segmentRom, s32 id, void* dst, size_t size) {
    if (!gAlreadyTranslated ) {
        gTranslatedAddress = DmaMgr_TranslateVromToRom(SEGMENT_ROM_START(icon_item_static_yar));
        gAlreadyTranslated = 1;
    }
    if (id == ITEM_SHIELD_MIRROR && segmentRom == gTranslatedAddress) {
        gCurIconIsMirrorShield = 1;
    } else {
        gCurIconIsMirrorShield = 0;
    } 
    gId = id;
    gDst = dst;
}

// Update Inventory Icons
RECOMP_HOOK_RETURN("CmpDma_LoadFileImpl") void return_CmpDma_LoadFileImpl(void) {
    if (gCurIconIsMirrorShield) {
        switch (recomp_get_config_u32("mirror_shield_design")) {
            case MIRROR_SHIELD_DESIGN_BASIC:
                Lib_MemCpy(gDst, gBasicMirrorShieldIcon_rgba32, ICON_ITEM_TEX_SIZE);
                break;
            case MIRROR_SHIELD_DESIGN_IKANA:
                Lib_MemCpy(gDst, gIkanaMirrorShieldIcon_rgba32, ICON_ITEM_TEX_SIZE);
                break;
            case MIRROR_SHIELD_DESIGN_CRESCENT:
                Lib_MemCpy(gDst, gCrescentMirrorShieldIcon_rgba32, ICON_ITEM_TEX_SIZE);
                break;
            case MIRROR_SHIELD_DESIGN_GERUDO:
                Lib_MemCpy(gDst, gGerudoMirrorShieldIcon_rgba32, ICON_ITEM_TEX_SIZE);
                break;
            case MIRROR_SHIELD_DESIGN_FACE:
                Lib_MemCpy(gDst, gFaceMirrorShieldIcon_rgba32, ICON_ITEM_TEX_SIZE);
                break;
        }
    }
    gCurIconIsMirrorShield = 0;
}

// Update Textures
RECOMP_HOOK("Player_UpdateCommon") void on_Player_UpdateCommon(Player* this, PlayState* play, Input* input) {
    static u8 oldConfigDesign = MIRROR_SHIELD_DESIGN_BASIC;
    u8 configDesign = recomp_get_config_u32("mirror_shield_design");
    if (configDesign != oldConfigDesign) {
        switch (configDesign) {
            case MIRROR_SHIELD_DESIGN_FACE:
                recomp_printf("Face");
                Lib_MemCpy(gCustomMirrorShieldTexture, gFaceMirrorShieldTexture, 4096);
                Lib_MemCpy(gCustomMirrorShieldRayTexture_i8, gFaceMirrorShieldRayTexture_i8, 4096);
                Lib_MemCpy(gGiCustomMirrorShieldTexture, gFaceMirrorShieldTexture, 4096);
                break;
            case MIRROR_SHIELD_DESIGN_BASIC:
                recomp_printf("Basic");
                Lib_MemCpy(gCustomMirrorShieldTexture, gBasicMirrorShieldTexture, 4096);
                Lib_MemCpy(gCustomMirrorShieldRayTexture_i8, gBasicMirrorShieldRayTexture_i8, 4096);
                Lib_MemCpy(gGiCustomMirrorShieldTexture, gBasicMirrorShieldTexture, 4096);
                break;
            case MIRROR_SHIELD_DESIGN_IKANA:
                recomp_printf("Ikana");
                Lib_MemCpy(gCustomMirrorShieldTexture, gIkanaMirrorShieldTexture, 4096);
                Lib_MemCpy(gCustomMirrorShieldRayTexture_i8, gIkanaMirrorShieldRayTexture_i8, 4096);
                Lib_MemCpy(gGiCustomMirrorShieldTexture, gIkanaMirrorShieldTexture, 4096);
                break;
            case MIRROR_SHIELD_DESIGN_CRESCENT:
                recomp_printf("Crescent");
                Lib_MemCpy(gCustomMirrorShieldTexture, gCrescentMirrorShieldTexture, 4096);
                Lib_MemCpy(gCustomMirrorShieldRayTexture_i8, gCrescentMirrorShieldRayTexture_i8, 4096);
                Lib_MemCpy(gGiCustomMirrorShieldTexture, gCrescentMirrorShieldTexture, 4096);
                break;
            case MIRROR_SHIELD_DESIGN_GERUDO:
                recomp_printf("Gerudo");
                Lib_MemCpy(gCustomMirrorShieldTexture, gGerudoMirrorShieldTexture, 4096);
                Lib_MemCpy(gCustomMirrorShieldRayTexture_i8, gGerudoMirrorShieldRayTexture_i8, 4096);
                Lib_MemCpy(gGiCustomMirrorShieldTexture, gGerudoMirrorShieldTexture, 4096);
                break;
        }
        oldConfigDesign = configDesign;
    }
}