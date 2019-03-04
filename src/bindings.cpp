#include "SkTypes.h"
#include "SkCanvas.h"
#include "SkColor.h"
#include "SkImageInfo.h"
#include "SkPaint.h"
#include "SkPath.h"
#include "SkRect.h"
#include "SkSurface.h"
#include "SkPicture.h"
#include "SkYUVAIndex.h"
#include "SkPoint3.h"
#include "SkRegion.h"
#include "SkFont.h"
#include "SkTypeface.h"
#include "SkFontMetrics.h"
#include "SkPictureRecorder.h"
#include "SkColorFilter.h"
#include "SkStrokeRec.h"
#include "SkMaskFilter.h"

#include "GrContext.h"

#if defined(SK_VULKAN)

#include "GrBackendSurface.h"
#include "vk/GrVkBackendContext.h"

#endif

//
// SkSurface
//

extern "C" SkSurface* C_SkSurface_MakeRasterN32Premul(int width, int height, const SkSurfaceProps* surfaceProps) {
    return SkSurface::MakeRasterN32Premul(width, height, surfaceProps).release();
}

extern "C" SkSurface* C_SkSurface_MakeRenderTarget(
    GrContext* context,
    SkBudgeted budgeted,
    const SkImageInfo* imageInfo) {
    return SkSurface::MakeRenderTarget(context, budgeted, *imageInfo).release();
}

extern "C" SkImage* C_SkSurface_makeImageSnapshot(SkSurface* self) {
    return self->makeImageSnapshot().release();
}

//
// SkImage
//

extern "C" SkImage* C_SkImage_MakeRasterData(const SkImageInfo* info, SkData* pixels, size_t rowBytes) {
    return SkImage::MakeRasterData(*info, sk_sp<SkData>(pixels), rowBytes).release();
}

extern "C" SkImage* C_SkImage_MakeFromBitmap(const SkBitmap* bitmap) {
    return SkImage::MakeFromBitmap(*bitmap).release();
}

extern "C" SkImage* C_SkImage_MakeFromEncoded(SkData* encoded, const SkIRect* subset) {
    return SkImage::MakeFromEncoded(sk_sp<SkData>(encoded), subset).release();
}

extern "C" SkImage* C_SkImage_MakeFromTexture(
        GrContext* context,
        const GrBackendTexture* backendTexture,
        GrSurfaceOrigin origin,
        SkColorType colorType,
        SkAlphaType alphaType,
        SkColorSpace* colorSpace) {
    return SkImage::MakeFromTexture(context, *backendTexture, origin, colorType, alphaType, sk_sp<SkColorSpace>(colorSpace)).release();
}

extern "C" SkImage* C_SkImage_MakeCrossContextFromEncoded(
        GrContext* context,
        SkData* data,
        bool buildMips,
        SkColorSpace* dstColorSpace,
        bool limitToMaxTextureSize
        ) {
    return SkImage::MakeCrossContextFromEncoded(context, sk_sp<SkData>(data), buildMips, dstColorSpace, limitToMaxTextureSize).release();
}

extern "C" SkImage* C_SkImage_MakeFromAdoptedTexture(
        GrContext* context,
        const GrBackendTexture* backendTexture,
        GrSurfaceOrigin origin,
        SkColorType colorType,
        SkAlphaType alphaType,
        SkColorSpace* colorSpace) {
    return SkImage::MakeFromAdoptedTexture(context, *backendTexture, origin, colorType, alphaType, sk_sp<SkColorSpace>(colorSpace)).release();
}

extern "C" SkImage* C_SkImage_MakeFromYUVATexturesCopy(
        GrContext* context,
        SkYUVColorSpace yuvColorSpace,
        const GrBackendTexture yuvaTextures[],
        const SkYUVAIndex yuvaIndices[4],
        SkISize imageSize,
        GrSurfaceOrigin imageOrigin,
        SkColorSpace* colorSpace) {
    return SkImage::MakeFromYUVATexturesCopy(context, yuvColorSpace, yuvaTextures, yuvaIndices, imageSize, imageOrigin, sk_sp<SkColorSpace>(colorSpace)).release();
}

extern "C" SkImage* C_SkImage_MakeFromYUVATexturesCopyWithExternalBackend(
        GrContext* context,
        SkYUVColorSpace yuvColorSpace,
        const GrBackendTexture yuvaTextures[],
        const SkYUVAIndex yuvaIndices[4],
        SkISize imageSize,
        GrSurfaceOrigin imageOrigin,
        const GrBackendTexture& backendTexture,
        SkColorSpace* colorSpace) {
    return SkImage::MakeFromYUVATexturesCopyWithExternalBackend(context, yuvColorSpace, yuvaTextures, yuvaIndices, imageSize, imageOrigin, backendTexture, sk_sp<SkColorSpace>(colorSpace)).release();
}

extern "C" SkImage* C_SkImage_MakeFromYUVATextures(
        GrContext* context,
        SkYUVColorSpace yuvColorSpace,
        const GrBackendTexture yuvaTextures[],
        const SkYUVAIndex yuvaIndices[4],
        SkISize imageSize,
        GrSurfaceOrigin imageOrigin,
        SkColorSpace* colorSpace) {
    return SkImage::MakeFromYUVATextures(context, yuvColorSpace, yuvaTextures, yuvaIndices, imageSize, imageOrigin, sk_sp<SkColorSpace>(colorSpace)).release();
}

extern "C" SkImage* C_SkImage_MakeFromNV12TexturesCopy(
        GrContext* context,
        SkYUVColorSpace yuvColorSpace,
        const GrBackendTexture nv12Textures[2],
        GrSurfaceOrigin imageOrigin,
        SkColorSpace* imageColorSpace) {
    return SkImage::MakeFromNV12TexturesCopy(context, yuvColorSpace, nv12Textures, imageOrigin, sk_sp<SkColorSpace>(imageColorSpace)).release();
}

extern "C" SkImage* C_SkImage_MakeFromNV12TexturesCopyWithExternalBackend(
        GrContext* context,
        SkYUVColorSpace yuvColorSpace,
        const GrBackendTexture nv12Textures[2],
        GrSurfaceOrigin imageOrigin,
        const GrBackendTexture* backendTexture,
        SkColorSpace* imageColorSpace) {
    return SkImage::MakeFromNV12TexturesCopyWithExternalBackend(context, yuvColorSpace, nv12Textures, imageOrigin, *backendTexture, sk_sp<SkColorSpace>(imageColorSpace)).release();
}

extern "C" SkImage* C_SkImage_MakeFromPicture(
        SkPicture* picture,
        const SkISize* dimensions,
        const SkMatrix* matrix,
        const SkPaint* paint,
        SkImage::BitDepth bitDepth,
        SkColorSpace* colorSpace) {
    return SkImage::MakeFromPicture(sk_sp<SkPicture>(picture), *dimensions, matrix, paint, bitDepth, sk_sp<SkColorSpace>(colorSpace)).release();
}

extern "C" void C_SkImage_getBackendTexture(
        const SkImage* self,
        bool flushPendingGrContextIO,
        GrSurfaceOrigin* origin,
        GrBackendTexture* result)
{
    *result = self->getBackendTexture(flushPendingGrContextIO, origin);
}

extern "C" SkData* C_SkImage_encodeToData(const SkImage* self, SkEncodedImageFormat imageFormat) {
    return self->encodeToData(imageFormat, 100).release();
}

extern "C" SkData* C_SkImage_refEncodedData(const SkImage* self) {
    return self->refEncodedData().release();
}

extern "C" SkImage* C_SkImage_makeSubset(const SkImage* self, const SkIRect* subset) {
    return self->makeSubset(*subset).release();
}

extern "C" SkImage* C_SkImage_makeTextureImage(const SkImage* self, GrContext* context, SkColorSpace* dstColorSpace, GrMipMapped mipMapped) {
    return self->makeTextureImage(context, dstColorSpace, mipMapped).release();
}

extern "C" SkImage* C_SkImage_makeNonTextureImage(const SkImage* self) {
    return self->makeNonTextureImage().release();
}

extern "C" SkImage* C_SkImage_makeRasterImage(const SkImage* self) {
    return self->makeRasterImage().release();
}

extern "C" SkImage* C_SkImage_makeColorSpace(const SkImage* self, SkColorSpace* target) {
    return self->makeColorSpace(sk_sp<SkColorSpace>(target)).release();
}

//
// SkData
//

extern "C" void C_SkData_ref(const SkData* self) {
    self->ref();
}

extern "C" void C_SkData_unref(const SkData* self) {
    self->unref();
}

//
// SkPaint
//

extern "C" void C_SkPaint_destruct(const SkPaint* self) {
    self->~SkPaint();
}

extern "C" void C_SkPaint_copy(SkPaint* self, const SkPaint* rhs) {
    *self = *rhs;
}

extern "C" bool C_SkPaint_Equals(const SkPaint* lhs, const SkPaint* rhs) {
    return *lhs == *rhs;
}

extern "C" void C_SkPaint_setColorFilter(SkPaint* self, SkColorFilter* colorFilter) {
    self->setColorFilter(sk_sp<SkColorFilter>(colorFilter));
}

extern "C" void C_SkPaint_setPathEffect(SkPaint* self, SkPathEffect* pathEffect) {
    self->setPathEffect(sk_sp<SkPathEffect>(pathEffect));
}

extern "C" void C_SkPaint_setMaskFilter(SkPaint* self, SkMaskFilter* maskFilter) {
    self->setMaskFilter(sk_sp<SkMaskFilter>(maskFilter));
}

extern "C" void C_SkPaint_setTypeface(SkPaint* self, SkTypeface* typeface) {
    self->setTypeface(sk_sp<SkTypeface>(typeface));
}

// postponed

/*
extern "C" void C_SkPaint_setImageFilter(SkPaint* self, SkImageFilter* imageFilter) {
    self->setImageFilter(sk_sp<SkImageFilter>(imageFilter));
}
*/

//
// SkPath
//

extern "C" void C_SkPath_destruct(const SkPath* self) {
    self->~SkPath();
}

extern "C" bool C_SkPath_Equals(const SkPath* lhs, const SkPath* rhs) {
    return *lhs == *rhs;
}

extern "C" SkData* C_SkPath_serialize(const SkPath* self) {
    return self->serialize().release();
}

extern "C" SkPath::FillType C_SkPath_ConvertToNonInverseFillType(SkPath::FillType fill) {
    return SkPath::ConvertToNonInverseFillType(fill);
}

//
// SkCanvas
// Note: bindgen layout is broken, so we are forced to allocate Canvas instances on the heap only.
//

extern "C" SkCanvas* C_SkCanvas_newEmpty() {
    return new SkCanvas();
}

extern "C" SkCanvas* C_SkCanvas_newWidthHeightAndProps(int width, int height, const SkSurfaceProps* props) {
    return new SkCanvas(width, height, props);
}

extern "C" SkCanvas* C_SkCanvas_newFromBitmap(const SkBitmap* bitmap) {
    return new SkCanvas(*bitmap);
}

extern "C" SkCanvas* C_SkCanvas_newFromBitmapAndProps(const SkBitmap* bitmap, const SkSurfaceProps* props) {
    return new SkCanvas(*bitmap, *props);
}

extern "C" void C_SkCanvas_delete(const SkCanvas* self) {
    delete self;
}

extern "C" SkCanvas* C_SkCanvas_MakeRasterDirect(const SkImageInfo* info, void* pixels, size_t row_bytes, const SkSurfaceProps* props) {
    return SkCanvas::MakeRasterDirect(*info, pixels, row_bytes, props).release();
}

extern "C" void C_SkCanvas_imageInfo(const SkCanvas* self, SkImageInfo* info) {
    *info = self->imageInfo();
}

extern "C" void C_SkCanvas_getBaseLayerSize(const SkCanvas* self, SkISize* size) {
    *size = self->getBaseLayerSize();
}

extern "C" SkSurface* C_SkCanvas_makeSurface(SkCanvas* self, const SkImageInfo* info, const SkSurfaceProps* props) {
    return self->makeSurface(*info, props).release();
}

extern "C" GrContext* C_SkCanvas_getGrContext(SkCanvas* self) {
    return self->getGrContext();
}

extern "C" bool C_SkCanvas_isClipEmpty(const SkCanvas* self) {
    return self->isClipEmpty();
}

extern "C" bool C_SkCanvas_isClipRect(const SkCanvas* self) {
    return self->isClipRect();
}

//
// SkImageInfo
//

extern "C" void C_SkImageInfo_Construct(SkImageInfo* uninitialized) {
    new (uninitialized) SkImageInfo();
}

extern "C" void C_SkImageInfo_Destruct(SkImageInfo* self) {
    self->~SkImageInfo();
}

extern "C" void C_SkImageInfo_Copy(const SkImageInfo* from, SkImageInfo* to) {
    *to = *from;
}

extern "C" void C_SkImageInfo_Make(SkImageInfo* self, int width, int height, SkColorType ct, SkAlphaType at, SkColorSpace* cs) {
    *self = SkImageInfo::Make(width, height, ct, at, sk_sp<SkColorSpace>(cs));
}

extern "C" void C_SkImageInfo_MakeS32(SkImageInfo* self, int width, int height, SkAlphaType at) {
    *self = SkImageInfo::MakeS32(width, height, at);
}

extern "C" SkColorSpace* C_SkImageInfo_colorSpace(const SkImageInfo* self) {
    // note: colorSpace returns just a pointer without increasing the reference counter.
    SkColorSpace* cs = self->colorSpace();
    if (cs) cs->ref();
    return cs;
}

//
// SkColorSpace
//

extern "C" void C_SkColorSpace_ref(const SkColorSpace* self) {
    self->ref();
}

extern "C" void C_SkColorSpace_unref(const SkColorSpace* self) {
    self->unref();
}

extern "C" SkColorSpace* C_SkColorSpace_MakeSRGB() {
    return SkColorSpace::MakeSRGB().release();
}

extern "C" SkColorSpace* C_SkColorSpace_MakeSRGBLinear() {
    return SkColorSpace::MakeSRGBLinear().release();
}

extern "C" SkColorSpace* C_SkColorSpace_MakeRGB(SkColorSpace::RenderTargetGamma gamma, SkColorSpace::Gamut gamut) {
    return SkColorSpace::MakeRGB(gamma, gamut).release();
}

extern "C" SkColorSpace* C_SkColorSpace_MakeRGB2(SkColorSpace::RenderTargetGamma gamma, const SkMatrix44* toXYZD50) {
    return SkColorSpace::MakeRGB(gamma, *toXYZD50).release();
}

extern "C" SkColorSpace* C_SkColorSpace_MakeRGB3(const SkColorSpaceTransferFn* coeffs, SkColorSpace::Gamut gamut) {
    return SkColorSpace::MakeRGB(*coeffs, gamut).release();
}

extern "C" SkColorSpace* C_SkColorSpace_MakeRGB4(const SkColorSpaceTransferFn* coeffs, const SkMatrix44* toXYZD50) {
    return SkColorSpace::MakeRGB(*coeffs, *toXYZD50).release();
}

extern "C" SkColorSpace* C_SkColorSpace_MakeRGB5(SkGammaNamed gammaNamed, const SkMatrix44* toXYZD50) {
    return SkColorSpace::MakeRGB(gammaNamed, *toXYZD50).release();
}

extern "C" SkColorSpace* C_SkColorSpace_makeLinearGamma(const SkColorSpace* self) {
    return self->makeLinearGamma().release();
}

extern "C" SkColorSpace* C_SkColorSpace_makeSRGBGamma(const SkColorSpace* self) {
    return self->makeSRGBGamma().release();
}

extern "C" SkColorSpace* C_SkColorSpace_makeColorSpin(const SkColorSpace* self) {
    return self->makeColorSpin().release();
}

extern "C" SkData* C_SkColorSpace_serialize(const SkColorSpace* self) {
    return self->serialize().release();
}

extern "C" SkColorSpace* C_SkColorSpace_Deserialize(const void* data, size_t length) {
    return SkColorSpace::Deserialize(data, length).release();
}

extern "C" SkGammaNamed C_SkColorSpace_gammaNamed(const SkColorSpace* self) {
    return self->gammaNamed();
}

//
// SkMatrix44
//

// calling SkMatrix44::new(Uninitialized) leads to linker error.
extern "C" void C_SkMatrix44_Construct(SkMatrix44* uninitialized) {
    new(uninitialized) SkMatrix44();
}

extern "C" void C_SkMatrix44_Destruct(SkMatrix44* self) {
    self->~SkMatrix44();
}

// SkMatrix44_Equals is not generated by bindgen.
extern "C" bool C_SkMatrix44_Equals(const SkMatrix44* self, const SkMatrix44* rhs) {
    return *self == *rhs;
}

// SkMatrix44_SkMatrix conversion.
extern "C" void C_SkMatrix44_SkMatrix(const SkMatrix44* self, SkMatrix* m) {
    *m = *self;
}

extern "C" void C_SkMatrix44_Mul(const SkMatrix44* self, const SkMatrix44* rhs, SkMatrix44* result) {
    *result = *self * *rhs;
}

extern "C" void C_SkMatrix44_MulV4(const SkMatrix44* self, const SkVector4* rhs, SkVector4* result) {
    *result = *self * *rhs;
}

//
// SkMatrix
//

extern "C" bool C_SkMatrix_Equals(const SkMatrix* self, const SkMatrix* rhs) {
    return *self == *rhs;
}

//
// SkSurfaceProps
//

extern "C" bool C_SkSurfaceProps_Equals(const SkSurfaceProps* self, const SkSurfaceProps* rhs) {
    return *self == *rhs;
}

//
// SkBitmap
//

extern "C" void C_SkBitmap_Construct(SkBitmap* uninitialized) {
    new (uninitialized) SkBitmap();
}

extern "C" void C_SkBitmap_Destruct(SkBitmap* self) {
    self->~SkBitmap();
}

extern "C" void C_SkBitmap_Copy(const SkBitmap* from, SkBitmap* to) {
    *to = *from;
}

extern "C" SkColorSpace* C_SkBitmap_colorSpace(const SkBitmap* self) {
    // note: colorSpace returns a pointer without increasing the reference counter.
    SkColorSpace* cs = self->colorSpace();
    if (cs) cs->ref();
    return cs;
}

extern "C" bool C_SkBitmap_ComputeIsOpaque(const SkBitmap* self) {
    return SkBitmap::ComputeIsOpaque(*self);
}

extern "C" bool C_SkBitmap_tryAllocN32Pixels(SkBitmap* self, int width, int height, bool isOpaque) {
    return self->tryAllocN32Pixels(width, height, isOpaque);
}

extern "C" bool C_SkBitmap_tryAllocPixels(SkBitmap* self) {
    return self->tryAllocPixels();
}

extern "C" bool C_SkBitmap_readyToDraw(const SkBitmap* self) {
    return self->readyToDraw();
}

extern "C" void C_SkBitmap_eraseARGB(const SkBitmap* self, U8CPU a, U8CPU r, U8CPU g, U8CPU b) {
    self->eraseARGB(a, r, g, b);
}

extern "C" float C_SkBitmap_getAlphaf(const SkBitmap* self, int x, int y) {
    return self->getAlphaf(x, y);
}

extern "C" bool C_SkBitmap_extractAlpha(const SkBitmap* self, SkBitmap* dst, const SkPaint* paint, SkIPoint* offset) {
    return self->extractAlpha(dst, paint, offset);
}

//
// SkPicture
//

extern "C" SkPicture* C_SkPicture_MakeFromData(const SkData* data) {
    return SkPicture::MakeFromData(data).release();
}

extern "C" SkData* C_SkPicture_serialize(const SkPicture* self) {
    return self->serialize().release();
}

extern "C" SkPicture* C_SkPicture_MakePlaceholder(const SkRect& cull) {
    return SkPicture::MakePlaceholder(cull).release();
}

extern "C" void C_SkPicture_playback(const SkPicture* self, SkCanvas* canvas) {
    self->playback(canvas);
}

extern "C" SkRect C_SkPicture_cullRect(const SkPicture* self) {
    return self->cullRect();
}

extern "C" int C_SkPicture_approximateOpCount(const SkPicture* self) {
    return self->approximateOpCount();
}

// note: returning size_t produces a linker error.
extern "C" void C_SkPicture_approximateBytesUsed(const SkPicture* self, size_t* out) {
    *out = self->approximateBytesUsed();
}

//
// SkRRect
//

extern "C" bool C_SkRRect_equals(const SkRRect* lhs, const SkRRect* rhs) {
    return *lhs == *rhs;
}

extern "C" bool C_SkRRect_not_equals(const SkRRect* lhs, const SkRRect* rhs) {
    return *lhs != *rhs;
}

//
// GrBackendTexture
//

extern "C" void C_GrBackendTexture_destruct(const GrBackendTexture* self) {
    self->~GrBackendTexture();
}

//
// SkRegion
//

extern "C" void C_SkRegion_destruct(SkRegion* region) {
    region->~SkRegion();
}

extern "C" bool C_SkRegion_equals(const SkRegion* lhs, const SkRegion* rhs) {
    return *lhs == *rhs;
}

//
// SkFontStyle
//

extern "C" bool C_SkFontStyle_equals(const SkFontStyle* lhs, const SkFontStyle* rhs) {
    return *lhs == *rhs;
}

//
// SkTypeface
//

extern "C" SkTypeface* C_SkTypeface_MakeDefault() {
    return SkTypeface::MakeDefault().release();
}

extern "C" SkTypeface* C_SkTypeface_MakeFromName(const char familyName[], SkFontStyle fontStyle) {
    return SkTypeface::MakeFromName(familyName, fontStyle).release();
}

extern "C" SkTypeface* C_SkTypeface_MakeFromFile(const char path[], int index) {
    return SkTypeface::MakeFromFile(path, index).release();
}

extern "C" SkTypeface* C_SkTypeface_MakeFromData(SkData* data, int index) {
    return SkTypeface::MakeFromData(sk_sp<SkData>(data), index).release();
}

extern "C" SkData* C_SkTypeface_serialize(const SkTypeface* self, SkTypeface::SerializeBehavior behavior) {
    return self->serialize(behavior).release();
}

//
// SkFont
//

extern "C" void C_SkFont_ConstructFromTypeface(SkFont* uninitialized, SkTypeface* typeface) {
    new(uninitialized) SkFont(sk_sp<SkTypeface>(typeface));
}

extern "C" void C_SkFont_ConstructFromTypefaceWithSize(SkFont* uninitialized, SkTypeface* typeface, SkScalar size) {
    new(uninitialized) SkFont(sk_sp<SkTypeface>(typeface), size);
}

extern "C" void C_SkFont_ConstructFromTypefaceWithSizeScaleAndSkew(SkFont* uninitialized, SkTypeface* typeface, SkScalar size, SkScalar scaleX, SkScalar skewX) {
    new(uninitialized) SkFont(sk_sp<SkTypeface>(typeface), size, scaleX, skewX);
}

extern "C" bool C_SkFont_equals(const SkFont* self, const SkFont* other) {
    return *self == *other;
}

extern "C" void C_SkFont_makeWithSize(const SkFont* self, SkScalar size, SkFont* result) {
    *result = self->makeWithSize(size);
}

extern "C" void C_SkFont_setTypeface(SkFont* self, SkTypeface* tf) {
    self->setTypeface(sk_sp<SkTypeface>(tf));
}

extern "C" void C_SkFont_Destruct(SkFont* self) {
    self->~SkFont();
}

//
// SkVertices
//

extern "C" void C_SkVertices_ref(const SkVertices* self) {
    self->ref();
}

extern "C" void C_SkVertices_unref(const SkVertices* self) {
    self->unref();
}

extern "C" SkVertices* C_SkVertices_MakeCopy(
    SkVertices::VertexMode mode, int vertexCount,
    const SkPoint positions[],
    const SkPoint texs[],
    const SkColor colors[],
    const SkVertices::BoneIndices boneIndices[],
    const SkVertices::BoneWeights boneWeights[],
    int indexCount,
    const uint16_t indices[],
    bool isVolatile) {
    return SkVertices::MakeCopy(mode, vertexCount, positions, texs, colors, boneIndices, boneWeights, indexCount, indices, isVolatile).release();
}

extern "C" SkVertices* C_SkVertices_applyBones(const SkVertices* self, const SkVertices::Bone bones[], int boneCount) {
    return self->applyBones(bones, boneCount).release();
}

extern "C" SkVertices* C_SkVertices_Decode(const void* buffer, size_t length) {
    return SkVertices::Decode(buffer, length).release();
}

extern "C" SkData* C_SkVertices_encode(const SkVertices* self) {
    return self->encode().release();
}

//
// SkVertices::Builder
//

extern "C" void C_SkVertices_Builder_destruct(SkVertices::Builder* builder) {
    builder->~Builder();
}

extern "C" SkVertices* C_SkVertices_Builder_detach(SkVertices::Builder* builder) {
    return builder->detach().release();
}

//
// SkPictureRecorder
//

extern "C" void C_SkPictureRecorder_destruct(SkPictureRecorder *self) {
    self->~SkPictureRecorder();
}

extern "C" SkPicture* C_SkPictureRecorder_finishRecordingAsPicture(SkPictureRecorder* self, const SkRect* cullRect) {
    if (cullRect){
        return self->finishRecordingAsPictureWithCull(*cullRect).release();
    } else {
        return self->finishRecordingAsPicture().release();
    }
}

//
// SkColorFilter
//

extern "C" SkColorFilter* C_SkColorFilter_MakeModeFilter(const SkColor* c, const SkBlendMode* blendMode) {
    return SkColorFilter::MakeModeFilter(*c, *blendMode).release();
}

extern "C" SkColorFilter* C_SkColorFilter_makeComposed(const SkColorFilter* self, SkColorFilter* inner) {
    return self->makeComposed(sk_sp<SkColorFilter>(inner)).release();
}

extern "C" SkColorFilter* C_SkColorFilter_MakeMatrixFilterRowMajor255(const SkScalar array[20]) {
    return SkColorFilter::MakeMatrixFilterRowMajor255(array).release();
}

extern "C" SkColorFilter* C_SkColorFilter_MakeLinearToSRGBGamma() {
    return SkColorFilter::MakeLinearToSRGBGamma().release();
}

extern "C" SkColorFilter* C_SkColorFilter_MakeSRGBToLinearGamma() {
    return SkColorFilter::MakeSRGBToLinearGamma().release();
}

extern "C" bool C_SkColorFilter_asColorMode(const SkColorFilter* self, SkColor* color, SkBlendMode* mode) {
    return self->asColorMode(color, mode);
}

extern "C" bool C_SkColorFilter_asColorMatrix(const SkColorFilter* self, SkScalar matrix[20]) {
    return self->asColorMatrix(matrix);
}

extern "C" bool C_SkColorFilter_asComponentTable(const SkColorFilter* self, SkBitmap* table) {
    return self->asComponentTable(table);
}

extern "C" uint32_t C_SkColorFilter_getFlags(const SkColorFilter* self) {
    return self->getFlags();
}

//
// SkStrokeRec
//

extern "C" void C_SkStrokeRec_destruct(SkStrokeRec* self) {
    self->~SkStrokeRec();
}

extern "C" void C_SkStrokeRec_copy(const SkStrokeRec* self, SkStrokeRec* other) {
    *other = *self;
}

extern "C" bool C_SkStrokeRec_hasEqualEffect(const SkStrokeRec* self, const SkStrokeRec* other) {
    return self->hasEqualEffect(*other);
}

//
// SkPathEffect
//

extern "C" SkPathEffect* C_SkPathEffect_MakeSum(SkPathEffect* first, SkPathEffect* second) {
    return SkPathEffect::MakeSum(sk_sp<SkPathEffect>(first), sk_sp<SkPathEffect>(second)).release();
}

extern "C" SkPathEffect* C_SkPathEffect_MakeCompose(SkPathEffect* outer, SkPathEffect* inner) {
    return SkPathEffect::MakeCompose(sk_sp<SkPathEffect>(outer), sk_sp<SkPathEffect>(inner)).release();
}

extern "C" void C_SkPathEffect_PointData_deletePoints(SkPathEffect::PointData* self) {
    delete [] self->fPoints;
    self->fPoints = nullptr;
}

//
// SkMaskFilter
//

extern "C" SkMaskFilter* C_SkMaskFilter_MakeBlur(SkBlurStyle style, SkScalar sigma, bool respectCTM) {
    return SkMaskFilter::MakeBlur(style, sigma, respectCTM).release();
}

extern "C" SkMaskFilter* C_SkMaskFilter_Compose(SkMaskFilter* outer, SkMaskFilter* inner) {
    return SkMaskFilter::MakeCompose(sk_sp<SkMaskFilter>(outer), sk_sp<SkMaskFilter>(inner)).release();
}

extern "C" SkMaskFilter* C_SkMaskFilter_Combine(SkMaskFilter* filterA, SkMaskFilter* filterB, SkCoverageMode coverageMode) {
    return SkMaskFilter::MakeCombine(sk_sp<SkMaskFilter>(filterA), sk_sp<SkMaskFilter>(filterB), coverageMode).release();
}

extern "C" SkMaskFilter* C_SkMaskFilter_makeWithMatrix(const SkMaskFilter* self, const SkMatrix* matrix) {
    return self->makeWithMatrix(*matrix).release();
}

//
// SkSize
//

extern "C" SkISize C_SkSize_toFloor(const SkSize* size) {
    return size->toFloor();
}

#if defined(SK_VULKAN)

extern "C" SkSurface* C_SkSurface_MakeFromBackendTexture(
    GrContext* context,
    const GrBackendTexture* backendTexture,
    GrSurfaceOrigin origin,
    int sampleCnt,
    SkColorType colorType) {
    return SkSurface::MakeFromBackendTexture(context, *backendTexture, origin, sampleCnt, colorType, nullptr, nullptr).release();
}

extern "C" void C_SkSurface_getBackendTexture(
        SkSurface* self,
        SkSurface::BackendHandleAccess handleAccess,
        GrBackendTexture* backendTexture) {
    *backendTexture = self->getBackendTexture(handleAccess);
}

// The GrVkBackendContext struct binding's length is too short
// because of the std::function that is used in it.

typedef PFN_vkVoidFunction (*GetProcFn)(const char* name, VkInstance instance, VkDevice device);
typedef const void* (*GetProcFnVoidPtr)(const char* name, VkInstance instance, VkDevice device);

extern "C" void* C_GrVkBackendContext_New(
        void* instance,
        void* physicalDevice,
        void* device,
        void* queue,
        uint32_t graphicsQueueIndex,

        /* PFN_vkVoidFunction makes us trouble on the Rust side */
        GetProcFnVoidPtr getProc) {

    auto& context = *new GrVkBackendContext();
    context.fInstance = static_cast<VkInstance>(instance);
    context.fPhysicalDevice = static_cast<VkPhysicalDevice>(physicalDevice);
    context.fDevice = static_cast<VkDevice>(device);
    context.fQueue = static_cast<VkQueue>(queue);
    context.fGraphicsQueueIndex = graphicsQueueIndex;

    context.fGetProc = *(reinterpret_cast<GetProcFn*>(&getProc));
    return &context;
}

extern "C" void C_GrVkBackendContext_Delete(void* vkBackendContext) {
    delete static_cast<GrVkBackendContext*>(vkBackendContext);
}

extern "C" GrContext* C_GrContext_MakeVulkan(const void* vkBackendContext) {
    return GrContext::MakeVulkan(*static_cast<const GrVkBackendContext*>(vkBackendContext)).release();
}

#endif