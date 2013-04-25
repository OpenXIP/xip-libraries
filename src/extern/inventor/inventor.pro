TEMPLATE = lib

TARGET = Inventor

# build a framework bundle on Mac OS X
macx::CONFIG += lib_bundle

CONFIG += dll exceptions shared thread ivgensources
CONFIG += opengl libFL libimage jpeg_static iconv

DESTDIR    = $(MEVIS_THIRDPARTY_LIB)/lib
DLLDESTDIR = $(MEVIS_THIRDPARTY_LIB)/lib

!win32::OBJECTS_DIR = obj

QMAKE_EXT_CPP += .c++

# postprocessing flags
MSVC_USE_SUBDIRS = 1

win32 {
  QMAKE_YACC = $(MEVIS_THIRDPARTY_LIB)/inventor/Inventor/build/windows/yacc.exe
  QMAKE_CXXFLAGS += /TP

  DEFINES += WIN32 INVENTOR_EXPORTS __SGIOIV_BUILD_DLL
  DEFINES += HAVE_BOOLEAN
  DEFINES -= UNICODE
  LIBS += Ws2_32.lib shell32.lib
}
else:macx {
  # see also end of file for mac framework config
  LIBS += -framework Carbon
}
else:unix:!macx {
  # ensure the local inttypes.h is found last
  QMAKE_CFLAGS   += -idirafter lib/mevis/include
  QMAKE_CXXFLAGS += -idirafter lib/mevis/include
}

debug::DEFINES += DEBUG

# this is required to define ${d}
isEmpty(TP_NO_SYSTEM_INCLUDE) {
  include( $(MEVIS_LIB)/make/systemInit.pro )
}

# libFL
libFL {
  INCLUDEPATH += \
    libFL/ang \
    libFL/src

  QMAKE_LIBDIR += libFL
  win32::LIBS += FL$${d}.lib
  unix ::LIBS += -lFL$${d}

  CONFIG += freetype
}

# libimage
libimage {
  QMAKE_LIBDIR += libimage
  win32::LIBS += image$${d}.lib
  unix ::LIBS += -limage$${d}
}

# include settings of required libraries
include( $(MEVIS_THIRDPARTY_LIB)/make/thirdpartyPackages.pro )

INCLUDEPATH += \
    lib/database/include \
    lib/interaction/include \
    lib/nodekits/include \
    lib/mevis/include
    
# nurbs
INCLUDEPATH += \
    lib/database/src/so/nodes \
    lib/database/src/so/nodes/nurbs \
    lib/database/src/so/nodes/nurbs/head
DEFINES += LIBRARYBUILD

#
#  MeVis extensions to Open Inventor
#

win32::HEADERS += \
    lib/mevis/include/SoWinEnterScope.h \
    lib/mevis/include/SoWinLeaveScope.h \
    lib/mevis/include/inttypes.h \
    lib/mevis/src/utf8_filesupport_win32.h

HEADERS += \
    lib/mevis/include/Inventor/SoCatch.h \
    lib/mevis/include/Inventor/SoInventor.h \
    lib/mevis/include/Inventor/SoMeVis.h \
    lib/mevis/include/Inventor/SoTrace.h \
    lib/mevis/include/Inventor/elements/SoGLPolygonOffsetElement.h \
    lib/mevis/include/Inventor/elements/SoGLStencilBitsElement.h \
    lib/mevis/include/Inventor/elements/SoPolygonOffsetElement.h \
    lib/mevis/include/Inventor/elements/SoStencilBitsElement.h \
    lib/mevis/include/Inventor/fields/SoSFVec2s.h \
    lib/mevis/include/Inventor/fields/SoSFVec3s.h \
    lib/mevis/include/Inventor/nodes/SoPolygonOffset.h \
    lib/mevis/include/Inventor/system/SbConfig.h \
    lib/mevis/include/Inventor/system/SbSystem.h

SOURCES += \
    lib/mevis/src/SoCatch.c++ \
    lib/mevis/src/SoMeVis.c++ \
    lib/mevis/src/SoTrace.c++ \
    lib/mevis/src/elements/SoGLPolygonOffsetElement.c++ \
    lib/mevis/src/elements/SoGLStencilBitsElement.c++ \
    lib/mevis/src/elements/SoPolygonOffsetElement.c++ \
    lib/mevis/src/elements/SoStencilBitsElement.c++ \
    lib/mevis/src/fields/SoSFVec2s.c++ \
    lib/mevis/src/fields/SoSFVec3s.c++ \
    lib/mevis/src/nodes/SoPolygonOffset.c++

win32::SOURCES += \
    lib/mevis/src/utf8_filesupport_win32.c++


#
#  SGI Open Inventor 2.1.x
#

unix:!macx::HEADERS += \
    lib/database/include/Inventor/SoOffscreenRenderer.h

unix:!macx::SOURCES += \
    lib/database/src/so/SoOffscreenRenderer.c++

HEADERS += \
    lib/database/include/Inventor/Sb.h \
    lib/database/include/Inventor/SbBasic.h \
    lib/database/include/Inventor/SbBox.h \
    lib/database/include/Inventor/SbColor.h \
    lib/database/include/Inventor/SbDict.h \
    lib/database/include/Inventor/SbLinear.h \
    lib/database/include/Inventor/SbPList.h \
    lib/database/include/Inventor/SbString.h \
    lib/database/include/Inventor/SbTime.h \
    lib/database/include/Inventor/SbViewportRegion.h \
    lib/database/include/Inventor/So.h \
    lib/database/include/Inventor/SoDB.h \
    lib/database/include/Inventor/SoInput.h \
    lib/database/include/Inventor/SoLists.h \
    lib/database/include/Inventor/SoOutput.h \
    lib/database/include/Inventor/SoPath.h \
    lib/database/include/Inventor/SoPickedPoint.h \
    lib/database/include/Inventor/SoPrimitiveVertex.h \
    lib/database/include/Inventor/SoType.h \
    lib/database/include/Inventor/actions/SoAction.h \
    lib/database/include/Inventor/actions/SoActions.h \
    lib/database/include/Inventor/actions/SoCallbackAction.h \
    lib/database/include/Inventor/actions/SoGLRenderAction.h \
    lib/database/include/Inventor/actions/SoGetBoundingBoxAction.h \
    lib/database/include/Inventor/actions/SoGetMatrixAction.h \
    lib/database/include/Inventor/actions/SoHandleEventAction.h \
    lib/database/include/Inventor/actions/SoPickAction.h \
    lib/database/include/Inventor/actions/SoRayPickAction.h \
    lib/database/include/Inventor/actions/SoSearchAction.h \
    lib/database/include/Inventor/actions/SoSubAction.h \
    lib/database/include/Inventor/actions/SoWriteAction.h \
    lib/database/include/Inventor/bundles/SoBundle.h \
    lib/database/include/Inventor/bundles/SoMaterialBundle.h \
    lib/database/include/Inventor/bundles/SoNormalBundle.h \
    lib/database/include/Inventor/bundles/SoTextureCoordinateBundle.h \
    lib/database/include/Inventor/caches/SoBoundingBoxCache.h \
    lib/database/include/Inventor/caches/SoCache.h \
    lib/database/include/Inventor/caches/SoGLCacheList.h \
    lib/database/include/Inventor/caches/SoGLRenderCache.h \
    lib/database/include/Inventor/caches/SoNormalCache.h \
    lib/database/include/Inventor/details/SoConeDetail.h \
    lib/database/include/Inventor/details/SoCubeDetail.h \
    lib/database/include/Inventor/details/SoCylinderDetail.h \
    lib/database/include/Inventor/details/SoDetail.h \
    lib/database/include/Inventor/details/SoDetails.h \
    lib/database/include/Inventor/details/SoFaceDetail.h \
    lib/database/include/Inventor/details/SoLineDetail.h \
    lib/database/include/Inventor/details/SoPointDetail.h \
    lib/database/include/Inventor/details/SoSubDetail.h \
    lib/database/include/Inventor/details/SoTextDetail.h \
    lib/database/include/Inventor/elements/SoAccumulatedElement.h \
    lib/database/include/Inventor/elements/SoAmbientColorElement.h \
    lib/database/include/Inventor/elements/SoBBoxModelMatrixElement.h \
    lib/database/include/Inventor/elements/SoCacheElement.h \
    lib/database/include/Inventor/elements/SoClipPlaneElement.h \
    lib/database/include/Inventor/elements/SoComplexityElement.h \
    lib/database/include/Inventor/elements/SoComplexityTypeElement.h \
    lib/database/include/Inventor/elements/SoCoordinateElement.h \
    lib/database/include/Inventor/elements/SoCreaseAngleElement.h \
    lib/database/include/Inventor/elements/SoCullVolumeElement.h \
    lib/database/include/Inventor/elements/SoCurrentGLMaterialElement.h \
    lib/database/include/Inventor/elements/SoDiffuseColorElement.h \
    lib/database/include/Inventor/elements/SoDrawStyleElement.h \
    lib/database/include/Inventor/elements/SoElement.h \
    lib/database/include/Inventor/elements/SoElements.h \
    lib/database/include/Inventor/elements/SoEmissiveColorElement.h \
    lib/database/include/Inventor/elements/SoFloatElement.h \
    lib/database/include/Inventor/elements/SoFocalDistanceElement.h \
    lib/database/include/Inventor/elements/SoFontNameElement.h \
    lib/database/include/Inventor/elements/SoFontSizeElement.h \
    lib/database/include/Inventor/elements/SoGLAmbientColorElement.h \
    lib/database/include/Inventor/elements/SoGLCacheContextElement.h \
    lib/database/include/Inventor/elements/SoGLClipPlaneElement.h \
    lib/database/include/Inventor/elements/SoGLColorIndexElement.h \
    lib/database/include/Inventor/elements/SoGLCoordinateElement.h \
    lib/database/include/Inventor/elements/SoGLDiffuseColorElement.h \
    lib/database/include/Inventor/elements/SoGLDrawStyleElement.h \
    lib/database/include/Inventor/elements/SoGLEmissiveColorElement.h \
    lib/database/include/Inventor/elements/SoGLLazyElement.h \
    lib/database/include/Inventor/elements/SoGLLightIdElement.h \
    lib/database/include/Inventor/elements/SoGLLightModelElement.h \
    lib/database/include/Inventor/elements/SoGLLinePatternElement.h \
    lib/database/include/Inventor/elements/SoGLLineWidthElement.h \
    lib/database/include/Inventor/elements/SoGLModelMatrixElement.h \
    lib/database/include/Inventor/elements/SoGLNormalElement.h \
    lib/database/include/Inventor/elements/SoGLPointSizeElement.h \
    lib/database/include/Inventor/elements/SoGLPolygonStippleElement.h \
    lib/database/include/Inventor/elements/SoGLProjectionMatrixElement.h \
    lib/database/include/Inventor/elements/SoGLRenderPassElement.h \
    lib/database/include/Inventor/elements/SoGLShapeHintsElement.h \
    lib/database/include/Inventor/elements/SoGLShininessElement.h \
    lib/database/include/Inventor/elements/SoGLSpecularColorElement.h \
    lib/database/include/Inventor/elements/SoGLTextureBlendColorElement.h \
    lib/database/include/Inventor/elements/SoGLTextureCoordinateElement.h \
    lib/database/include/Inventor/elements/SoGLTextureEnabledElement.h \
    lib/database/include/Inventor/elements/SoGLTextureImageElement.h \
    lib/database/include/Inventor/elements/SoGLTextureMatrixElement.h \
    lib/database/include/Inventor/elements/SoGLTextureModelElement.h \
    lib/database/include/Inventor/elements/SoGLTextureQualityElement.h \
    lib/database/include/Inventor/elements/SoGLTextureWrapSElement.h \
    lib/database/include/Inventor/elements/SoGLTextureWrapTElement.h \
    lib/database/include/Inventor/elements/SoGLUpdateAreaElement.h \
    lib/database/include/Inventor/elements/SoGLViewingMatrixElement.h \
    lib/database/include/Inventor/elements/SoGLViewportRegionElement.h \
    lib/database/include/Inventor/elements/SoInt32Element.h \
    lib/database/include/Inventor/elements/SoLazyElement.h \
    lib/database/include/Inventor/elements/SoLightAttenuationElement.h \
    lib/database/include/Inventor/elements/SoLightModelElement.h \
    lib/database/include/Inventor/elements/SoLinePatternElement.h \
    lib/database/include/Inventor/elements/SoLineWidthElement.h \
    lib/database/include/Inventor/elements/SoLocalBBoxMatrixElement.h \
    lib/database/include/Inventor/elements/SoLongElement.h \
    lib/database/include/Inventor/elements/SoMaterialBindingElement.h \
    lib/database/include/Inventor/elements/SoModelMatrixElement.h \
    lib/database/include/Inventor/elements/SoNormalBindingElement.h \
    lib/database/include/Inventor/elements/SoNormalElement.h \
    lib/database/include/Inventor/elements/SoOverrideElement.h \
    lib/database/include/Inventor/elements/SoPickRayElement.h \
    lib/database/include/Inventor/elements/SoPickStyleElement.h \
    lib/database/include/Inventor/elements/SoPointSizeElement.h \
    lib/database/include/Inventor/elements/SoProfileCoordinateElement.h \
    lib/database/include/Inventor/elements/SoProfileElement.h \
    lib/database/include/Inventor/elements/SoProjectionMatrixElement.h \
    lib/database/include/Inventor/elements/SoReplacedElement.h \
    lib/database/include/Inventor/elements/SoShapeHintsElement.h \
    lib/database/include/Inventor/elements/SoShapeStyleElement.h \
    lib/database/include/Inventor/elements/SoShininessElement.h \
    lib/database/include/Inventor/elements/SoSpecularColorElement.h \
    lib/database/include/Inventor/elements/SoSubElement.h \
    lib/database/include/Inventor/elements/SoSwitchElement.h \
    lib/database/include/Inventor/elements/SoTextureBlendColorElement.h \
    lib/database/include/Inventor/elements/SoTextureCoordinateBindingElement.h \
    lib/database/include/Inventor/elements/SoTextureCoordinateElement.h \
    lib/database/include/Inventor/elements/SoTextureImageElement.h \
    lib/database/include/Inventor/elements/SoTextureMatrixElement.h \
    lib/database/include/Inventor/elements/SoTextureModelElement.h \
    lib/database/include/Inventor/elements/SoTextureQualityElement.h \
    lib/database/include/Inventor/elements/SoTextureWrapSElement.h \
    lib/database/include/Inventor/elements/SoTextureWrapTElement.h \
    lib/database/include/Inventor/elements/SoTransparencyElement.h \
    lib/database/include/Inventor/elements/SoUnitsElement.h \
    lib/database/include/Inventor/elements/SoViewVolumeElement.h \
    lib/database/include/Inventor/elements/SoViewingMatrixElement.h \
    lib/database/include/Inventor/elements/SoViewportRegionElement.h \
    lib/database/include/Inventor/elements/SoWindowElement.h \
    lib/database/include/Inventor/engines/SoBoolOperation.h \
    lib/database/include/Inventor/engines/SoCalculator.h \
    lib/database/include/Inventor/engines/SoCompose.h \
    lib/database/include/Inventor/engines/SoComputeBoundingBox.h \
    lib/database/include/Inventor/engines/SoConcatenate.h \
    lib/database/include/Inventor/engines/SoCounter.h \
    lib/database/include/Inventor/engines/SoElapsedTime.h \
    lib/database/include/Inventor/engines/SoEngine.h \
    lib/database/include/Inventor/engines/SoEngines.h \
    lib/database/include/Inventor/engines/SoFieldConverter.h \
    lib/database/include/Inventor/engines/SoGate.h \
    lib/database/include/Inventor/engines/SoInterpolate.h \
    lib/database/include/Inventor/engines/SoOnOff.h \
    lib/database/include/Inventor/engines/SoOneShot.h \
    lib/database/include/Inventor/engines/SoOutputData.h \
    lib/database/include/Inventor/engines/SoSelectOne.h \
    lib/database/include/Inventor/engines/SoSubEngine.h \
    lib/database/include/Inventor/engines/SoTimeCounter.h \
    lib/database/include/Inventor/engines/SoTransformVec3f.h \
    lib/database/include/Inventor/engines/SoTriggerAny.h \
    lib/database/include/Inventor/errors/SoDebugError.h \
    lib/database/include/Inventor/errors/SoError.h \
    lib/database/include/Inventor/errors/SoErrors.h \
    lib/database/include/Inventor/errors/SoMemoryError.h \
    lib/database/include/Inventor/errors/SoReadError.h \
    lib/database/include/Inventor/events/SoButtonEvent.h \
    lib/database/include/Inventor/events/SoEvent.h \
    lib/database/include/Inventor/events/SoEvents.h \
    lib/database/include/Inventor/events/SoKeyboardEvent.h \
    lib/database/include/Inventor/events/SoLocation2Event.h \
    lib/database/include/Inventor/events/SoMotion3Event.h \
    lib/database/include/Inventor/events/SoMouseButtonEvent.h \
    lib/database/include/Inventor/events/SoSpaceballButtonEvent.h \
    lib/database/include/Inventor/events/SoSubEvent.h \
    lib/database/include/Inventor/fields/SoField.h \
    lib/database/include/Inventor/fields/SoFieldContainer.h \
    lib/database/include/Inventor/fields/SoFieldData.h \
    lib/database/include/Inventor/fields/SoFields.h \
    lib/database/include/Inventor/fields/SoMFBitMask.h \
    lib/database/include/Inventor/fields/SoMFBool.h \
    lib/database/include/Inventor/fields/SoMFColor.h \
    lib/database/include/Inventor/fields/SoMFEngine.h \
    lib/database/include/Inventor/fields/SoMFEnum.h \
    lib/database/include/Inventor/fields/SoMFFloat.h \
    lib/database/include/Inventor/fields/SoMFInt32.h \
    lib/database/include/Inventor/fields/SoMFLong.h \
    lib/database/include/Inventor/fields/SoMFMatrix.h \
    lib/database/include/Inventor/fields/SoMFName.h \
    lib/database/include/Inventor/fields/SoMFNode.h \
    lib/database/include/Inventor/fields/SoMFPath.h \
    lib/database/include/Inventor/fields/SoMFPlane.h \
    lib/database/include/Inventor/fields/SoMFRotation.h \
    lib/database/include/Inventor/fields/SoMFShort.h \
    lib/database/include/Inventor/fields/SoMFString.h \
    lib/database/include/Inventor/fields/SoMFTime.h \
    lib/database/include/Inventor/fields/SoMFUInt32.h \
    lib/database/include/Inventor/fields/SoMFULong.h \
    lib/database/include/Inventor/fields/SoMFUShort.h \
    lib/database/include/Inventor/fields/SoMFVec2f.h \
    lib/database/include/Inventor/fields/SoMFVec3f.h \
    lib/database/include/Inventor/fields/SoMFVec4f.h \
    lib/database/include/Inventor/fields/SoSFBitMask.h \
    lib/database/include/Inventor/fields/SoSFBool.h \
    lib/database/include/Inventor/fields/SoSFColor.h \
    lib/database/include/Inventor/fields/SoSFEngine.h \
    lib/database/include/Inventor/fields/SoSFEnum.h \
    lib/database/include/Inventor/fields/SoSFFloat.h \
    lib/database/include/Inventor/fields/SoSFImage.h \
    lib/database/include/Inventor/fields/SoSFInt32.h \
    lib/database/include/Inventor/fields/SoSFLong.h \
    lib/database/include/Inventor/fields/SoSFMatrix.h \
    lib/database/include/Inventor/fields/SoSFName.h \
    lib/database/include/Inventor/fields/SoSFNode.h \
    lib/database/include/Inventor/fields/SoSFPath.h \
    lib/database/include/Inventor/fields/SoSFPlane.h \
    lib/database/include/Inventor/fields/SoSFRotation.h \
    lib/database/include/Inventor/fields/SoSFShort.h \
    lib/database/include/Inventor/fields/SoSFString.h \
    lib/database/include/Inventor/fields/SoSFTime.h \
    lib/database/include/Inventor/fields/SoSFTrigger.h \
    lib/database/include/Inventor/fields/SoSFUInt32.h \
    lib/database/include/Inventor/fields/SoSFULong.h \
    lib/database/include/Inventor/fields/SoSFUShort.h \
    lib/database/include/Inventor/fields/SoSFVec2f.h \
    lib/database/include/Inventor/fields/SoSFVec3f.h \
    lib/database/include/Inventor/fields/SoSFVec4f.h \
    lib/database/include/Inventor/fields/SoSubField.h \
    lib/database/include/Inventor/misc/SoAuditorList.h \
    lib/database/include/Inventor/misc/SoBase.h \
    lib/database/include/Inventor/misc/SoBasic.h \
    lib/database/include/Inventor/misc/SoByteStream.h \
    lib/database/include/Inventor/misc/SoCallbackList.h \
    lib/database/include/Inventor/misc/SoChildList.h \
    lib/database/include/Inventor/misc/SoCompactPathList.h \
    lib/database/include/Inventor/misc/SoNormalGenerator.h \
    lib/database/include/Inventor/misc/SoNotification.h \
    lib/database/include/Inventor/misc/SoState.h \
    lib/database/include/Inventor/misc/SoTempPath.h \
    lib/database/include/Inventor/misc/SoTranscribe.h \
    lib/database/include/Inventor/misc/upgraders/SoUpgrader.h \
    lib/database/include/Inventor/misc/upgraders/SoV1CustomNode.h \
    lib/database/include/Inventor/nodes/SoAnnotation.h \
    lib/database/include/Inventor/nodes/SoArray.h \
    lib/database/include/Inventor/nodes/SoAsciiText.h \
    lib/database/include/Inventor/nodes/SoBaseColor.h \
    lib/database/include/Inventor/nodes/SoBlinker.h \
    lib/database/include/Inventor/nodes/SoCallback.h \
    lib/database/include/Inventor/nodes/SoCamera.h \
    lib/database/include/Inventor/nodes/SoClipPlane.h \
    lib/database/include/Inventor/nodes/SoColorIndex.h \
    lib/database/include/Inventor/nodes/SoComplexity.h \
    lib/database/include/Inventor/nodes/SoCone.h \
    lib/database/include/Inventor/nodes/SoCoordinate3.h \
    lib/database/include/Inventor/nodes/SoCoordinate4.h \
    lib/database/include/Inventor/nodes/SoCube.h \
    lib/database/include/Inventor/nodes/SoCylinder.h \
    lib/database/include/Inventor/nodes/SoDirectionalLight.h \
    lib/database/include/Inventor/nodes/SoDrawStyle.h \
    lib/database/include/Inventor/nodes/SoEnvironment.h \
    lib/database/include/Inventor/nodes/SoEventCallback.h \
    lib/database/include/Inventor/nodes/SoFaceSet.h \
    lib/database/include/Inventor/nodes/SoFile.h \
    lib/database/include/Inventor/nodes/SoFont.h \
    lib/database/include/Inventor/nodes/SoFontStyle.h \
    lib/database/include/Inventor/nodes/SoGroup.h \
    lib/database/include/Inventor/nodes/SoIndexedFaceSet.h \
    lib/database/include/Inventor/nodes/SoIndexedLineSet.h \
    lib/database/include/Inventor/nodes/SoIndexedNurbsCurve.h \
    lib/database/include/Inventor/nodes/SoIndexedNurbsSurface.h \
    lib/database/include/Inventor/nodes/SoIndexedShape.h \
    lib/database/include/Inventor/nodes/SoIndexedTriangleStripSet.h \
    lib/database/include/Inventor/nodes/SoInfo.h \
    lib/database/include/Inventor/nodes/SoLOD.h \
    lib/database/include/Inventor/nodes/SoLabel.h \
    lib/database/include/Inventor/nodes/SoLevelOfDetail.h \
    lib/database/include/Inventor/nodes/SoLight.h \
    lib/database/include/Inventor/nodes/SoLightModel.h \
    lib/database/include/Inventor/nodes/SoLineSet.h \
    lib/database/include/Inventor/nodes/SoLinearProfile.h \
    lib/database/include/Inventor/nodes/SoLocateHighlight.h \
    lib/database/include/Inventor/nodes/SoMaterial.h \
    lib/database/include/Inventor/nodes/SoMaterialBinding.h \
    lib/database/include/Inventor/nodes/SoMaterialIndex.h \
    lib/database/include/Inventor/nodes/SoMatrixTransform.h \
    lib/database/include/Inventor/nodes/SoMultipleCopy.h \
    lib/database/include/Inventor/nodes/SoNode.h \
    lib/database/include/Inventor/nodes/SoNodes.h \
    lib/database/include/Inventor/nodes/SoNonIndexedShape.h \
    lib/database/include/Inventor/nodes/SoNormal.h \
    lib/database/include/Inventor/nodes/SoNormalBinding.h \
    lib/database/include/Inventor/nodes/SoNurbsCurve.h \
    lib/database/include/Inventor/nodes/SoNurbsProfile.h \
    lib/database/include/Inventor/nodes/SoNurbsSurface.h \
    lib/database/include/Inventor/nodes/SoOrthographicCamera.h \
    lib/database/include/Inventor/nodes/SoPackedColor.h \
    lib/database/include/Inventor/nodes/SoPathSwitch.h \
    lib/database/include/Inventor/nodes/SoPendulum.h \
    lib/database/include/Inventor/nodes/SoPerspectiveCamera.h \
    lib/database/include/Inventor/nodes/SoPickStyle.h \
    lib/database/include/Inventor/nodes/SoPointLight.h \
    lib/database/include/Inventor/nodes/SoPointSet.h \
    lib/database/include/Inventor/nodes/SoProfile.h \
    lib/database/include/Inventor/nodes/SoProfileCoordinate2.h \
    lib/database/include/Inventor/nodes/SoProfileCoordinate3.h \
    lib/database/include/Inventor/nodes/SoQuadMesh.h \
    lib/database/include/Inventor/nodes/SoResetTransform.h \
    lib/database/include/Inventor/nodes/SoRotation.h \
    lib/database/include/Inventor/nodes/SoRotationXYZ.h \
    lib/database/include/Inventor/nodes/SoRotor.h \
    lib/database/include/Inventor/nodes/SoScale.h \
    lib/database/include/Inventor/nodes/SoSeparator.h \
    lib/database/include/Inventor/nodes/SoShape.h \
    lib/database/include/Inventor/nodes/SoShapeHints.h \
    lib/database/include/Inventor/nodes/SoShuttle.h \
    lib/database/include/Inventor/nodes/SoSphere.h \
    lib/database/include/Inventor/nodes/SoSpotLight.h \
    lib/database/include/Inventor/nodes/SoSubNode.h \
    lib/database/include/Inventor/nodes/SoSwitch.h \
    lib/database/include/Inventor/nodes/SoText2.h \
    lib/database/include/Inventor/nodes/SoText3.h \
    lib/database/include/Inventor/nodes/SoTexture2.h \
    lib/database/include/Inventor/nodes/SoTexture2Transform.h \
    lib/database/include/Inventor/nodes/SoTextureCoordinate2.h \
    lib/database/include/Inventor/nodes/SoTextureCoordinateBinding.h \
    lib/database/include/Inventor/nodes/SoTextureCoordinateDefault.h \
    lib/database/include/Inventor/nodes/SoTextureCoordinateEnvironment.h \
    lib/database/include/Inventor/nodes/SoTextureCoordinateFunction.h \
    lib/database/include/Inventor/nodes/SoTextureCoordinatePlane.h \
    lib/database/include/Inventor/nodes/SoTransform.h \
    lib/database/include/Inventor/nodes/SoTransformSeparator.h \
    lib/database/include/Inventor/nodes/SoTransformation.h \
    lib/database/include/Inventor/nodes/SoTranslation.h \
    lib/database/include/Inventor/nodes/SoTriangleStripSet.h \
    lib/database/include/Inventor/nodes/SoUnits.h \
    lib/database/include/Inventor/nodes/SoVertexArray.h \
    lib/database/include/Inventor/nodes/SoVertexProperty.h \
    lib/database/include/Inventor/nodes/SoVertexShape.h \
    lib/database/include/Inventor/nodes/SoWWWAnchor.h \
    lib/database/include/Inventor/nodes/SoWWWInline.h \
    lib/database/include/Inventor/nodes/glVertArray.h \
    lib/database/include/Inventor/projectors/SbCylinderPlaneProjector.h \
    lib/database/include/Inventor/projectors/SbCylinderProjector.h \
    lib/database/include/Inventor/projectors/SbCylinderSectionProjector.h \
    lib/database/include/Inventor/projectors/SbCylinderSheetProjector.h \
    lib/database/include/Inventor/projectors/SbLineProjector.h \
    lib/database/include/Inventor/projectors/SbPlaneProjector.h \
    lib/database/include/Inventor/projectors/SbProjector.h \
    lib/database/include/Inventor/projectors/SbProjectors.h \
    lib/database/include/Inventor/projectors/SbSpherePlaneProjector.h \
    lib/database/include/Inventor/projectors/SbSphereProjector.h \
    lib/database/include/Inventor/projectors/SbSphereSectionProjector.h \
    lib/database/include/Inventor/projectors/SbSphereSheetProjector.h \
    lib/database/include/Inventor/sensors/SoAlarmSensor.h \
    lib/database/include/Inventor/sensors/SoDataSensor.h \
    lib/database/include/Inventor/sensors/SoDelayQueueSensor.h \
    lib/database/include/Inventor/sensors/SoFieldSensor.h \
    lib/database/include/Inventor/sensors/SoIdleSensor.h \
    lib/database/include/Inventor/sensors/SoNodeSensor.h \
    lib/database/include/Inventor/sensors/SoOneShotSensor.h \
    lib/database/include/Inventor/sensors/SoPathSensor.h \
    lib/database/include/Inventor/sensors/SoSensor.h \
    lib/database/include/Inventor/sensors/SoSensorManager.h \
    lib/database/include/Inventor/sensors/SoSensors.h \
    lib/database/include/Inventor/sensors/SoTimerQueueSensor.h \
    lib/database/include/Inventor/sensors/SoTimerSensor.h \
    lib/database/include/SoDebug.h \
    lib/database/include/SoUnknownEngine.h \
    lib/database/include/SoUnknownNode.h \
    lib/database/include/machine.h \
    lib/database/src/so/engines/SoCalcExpr.h \
    lib/database/src/so/engines/SoEngineUtil.h \
    lib/database/src/so/engines/SoFieldConverters.h \
    lib/database/src/so/fields/SoGlobalField.h \
    lib/database/src/so/nodes/nurbs/SoAddPrefix.h \
    lib/database/src/so/nodes/nurbs/SoCurveMaps.h \
    lib/database/src/so/nodes/nurbs/SoCurveRender.h \
    lib/database/src/so/nodes/nurbs/SoCurveRenderEval.h \
    lib/database/src/so/nodes/nurbs/SoGLRender.h \
    lib/database/src/so/nodes/nurbs/SoPickEvals.h \
    lib/database/src/so/nodes/nurbs/SoPickMaps.h \
    lib/database/src/so/nodes/nurbs/SoPickRender.h \
    lib/database/src/so/nodes/nurbs/SoPrimEvals.h \
    lib/database/src/so/nodes/nurbs/SoPrimMaps.h \
    lib/database/src/so/nodes/nurbs/SoPrimRender.h \
    lib/database/src/so/nodes/nurbs/_defines.h \
    lib/database/src/so/nodes/nurbs/_undefs.h \
    lib/database/src/so/nodes/nurbs/clients/gl4base.h \
    lib/database/src/so/nodes/nurbs/clients/gl4curveval.h \
    lib/database/src/so/nodes/nurbs/clients/gl4surfeval.h \
    lib/database/src/so/nodes/nurbs/clients/gl4types.h \
    lib/database/src/so/nodes/nurbs/clients/isocurveeval.h \
    lib/database/src/so/nodes/nurbs/clients/softcurvemaps.h \
    lib/database/src/so/nodes/nurbs/clients/softcurveval.h \
    lib/database/src/so/nodes/nurbs/clients/softcurvmap.h \
    lib/database/src/so/nodes/nurbs/clients/softrenderer.h \
    lib/database/src/so/nodes/nurbs/clients/softsurfacemaps.h \
    lib/database/src/so/nodes/nurbs/clients/softsurfeval.h \
    lib/database/src/so/nodes/nurbs/clients/softsurfmap.h \
    lib/database/src/so/nodes/nurbs/clients/typestringtable.h \
    lib/database/src/so/nodes/nurbs/head/arc.h \
    lib/database/src/so/nodes/nurbs/head/arcsorter.h \
    lib/database/src/so/nodes/nurbs/head/arctess.h \
    lib/database/src/so/nodes/nurbs/head/backend.h \
    lib/database/src/so/nodes/nurbs/head/basiccrveval.h \
    lib/database/src/so/nodes/nurbs/head/basicsurfeval.h \
    lib/database/src/so/nodes/nurbs/head/bezierarc.h \
    lib/database/src/so/nodes/nurbs/head/bin.h \
    lib/database/src/so/nodes/nurbs/head/bufpool.h \
    lib/database/src/so/nodes/nurbs/head/cachingeval.h \
    lib/database/src/so/nodes/nurbs/head/coveandtiler.h \
    lib/database/src/so/nodes/nurbs/head/curve.h \
    lib/database/src/so/nodes/nurbs/head/curvelist.h \
    lib/database/src/so/nodes/nurbs/head/defines.h \
    lib/database/src/so/nodes/nurbs/head/displaylist.h \
    lib/database/src/so/nodes/nurbs/head/displaymode.h \
    lib/database/src/so/nodes/nurbs/head/flist.h \
    lib/database/src/so/nodes/nurbs/head/flistsorter.h \
    lib/database/src/so/nodes/nurbs/head/glimports.h \
    lib/database/src/so/nodes/nurbs/head/gridline.h \
    lib/database/src/so/nodes/nurbs/head/gridtrimvertex.h \
    lib/database/src/so/nodes/nurbs/head/gridvertex.h \
    lib/database/src/so/nodes/nurbs/head/hull.h \
    lib/database/src/so/nodes/nurbs/head/jarcloc.h \
    lib/database/src/so/nodes/nurbs/head/jumpbuffer.h \
    lib/database/src/so/nodes/nurbs/head/knot.h \
    lib/database/src/so/nodes/nurbs/head/knotvector.h \
    lib/database/src/so/nodes/nurbs/head/mapdesc.h \
    lib/database/src/so/nodes/nurbs/head/maplist.h \
    lib/database/src/so/nodes/nurbs/head/mesher.h \
    lib/database/src/so/nodes/nurbs/head/myassert.h \
    lib/database/src/so/nodes/nurbs/head/myglimports.h \
    lib/database/src/so/nodes/nurbs/head/mymath.h \
    lib/database/src/so/nodes/nurbs/head/mysetjmp.h \
    lib/database/src/so/nodes/nurbs/head/mystdio.h \
    lib/database/src/so/nodes/nurbs/head/mystdlib.h \
    lib/database/src/so/nodes/nurbs/head/mystring.h \
    lib/database/src/so/nodes/nurbs/head/nurbsconsts.h \
    lib/database/src/so/nodes/nurbs/head/nurbstess.h \
    lib/database/src/so/nodes/nurbs/head/patch.h \
    lib/database/src/so/nodes/nurbs/head/patchlist.h \
    lib/database/src/so/nodes/nurbs/head/pwlarc.h \
    lib/database/src/so/nodes/nurbs/head/quilt.h \
    lib/database/src/so/nodes/nurbs/head/reader.h \
    lib/database/src/so/nodes/nurbs/head/renderhints.h \
    lib/database/src/so/nodes/nurbs/head/simplemath.h \
    lib/database/src/so/nodes/nurbs/head/slicer.h \
    lib/database/src/so/nodes/nurbs/head/sorter.h \
    lib/database/src/so/nodes/nurbs/head/subdivider.h \
    lib/database/src/so/nodes/nurbs/head/trimline.h \
    lib/database/src/so/nodes/nurbs/head/trimregion.h \
    lib/database/src/so/nodes/nurbs/head/trimvertex.h \
    lib/database/src/so/nodes/nurbs/head/trimvertpool.h \
    lib/database/src/so/nodes/nurbs/head/types.h \
    lib/database/src/so/nodes/nurbs/head/uarray.h \
    lib/database/src/so/nodes/nurbs/head/varray.h \
    lib/database/src/so/nodes/readGIF.h \
    lib/database/src/so/upgraders/SoUpgraders.h \
    lib/database/src/so/upgraders/SoV1DrawStyle.h \
    lib/database/src/so/upgraders/SoV1Environment.h \
    lib/database/src/so/upgraders/SoV1IndexedTriangleMesh.h \
    lib/database/src/so/upgraders/SoV1LayerGroup.h \
    lib/database/src/so/upgraders/SoV1LightModel.h \
    lib/database/src/so/upgraders/SoV1Material.h \
    lib/database/src/so/upgraders/SoV1PackedColor.h \
    lib/database/src/so/upgraders/SoV1PickStyle.h \
    lib/database/src/so/upgraders/SoV1Separator.h \
    lib/database/src/so/upgraders/SoV1ShapeHints.h \
    lib/database/src/so/upgraders/SoV1Text2.h \
    lib/database/src/so/upgraders/SoV1Text3.h \
    lib/database/src/so/upgraders/SoV1Texture2.h \
    lib/database/src/so/upgraders/SoV1TextureCoordinateCube.h \
    lib/database/src/so/upgraders/SoV1TextureCoordinateCylinder.h \
    lib/database/src/so/upgraders/SoV1TextureCoordinateEnvironment.h \
    lib/database/src/so/upgraders/SoV1TextureCoordinatePlane.h \
    lib/database/src/so/upgraders/SoV1TextureCoordinateSphere.h \
    lib/database/src/so/upgraders/SoV2AsciiText.h \
    lib/database/src/so/upgraders/SoV2FontStyle.h \
    lib/database/src/so/upgraders/SoV2LOD.h \
    lib/database/src/so/upgraders/SoV2MaterialIndex.h \
    lib/database/src/so/upgraders/SoV2Text2.h \
    lib/database/src/so/upgraders/SoV2Text3.h \
    lib/database/src/so/upgraders/SoV2VertexProperty.h \
    lib/database/src/so/upgraders/SoV2WWWAnchor.h \
    lib/database/src/so/upgraders/SoV2WWWInline.h \
    lib/interaction/include/Inventor/SoInteraction.h \
    lib/interaction/include/Inventor/SoSceneManager.h \
    lib/interaction/include/Inventor/actions/SoBoxHighlightRenderAction.h \
    lib/interaction/include/Inventor/actions/SoLineHighlightRenderAction.h \
    lib/interaction/include/Inventor/draggers/SoCenterballDragger.h \
    lib/interaction/include/Inventor/draggers/SoDirectionalLightDragger.h \
    lib/interaction/include/Inventor/draggers/SoDragPointDragger.h \
    lib/interaction/include/Inventor/draggers/SoDragger.h \
    lib/interaction/include/Inventor/draggers/SoHandleBoxDragger.h \
    lib/interaction/include/Inventor/draggers/SoJackDragger.h \
    lib/interaction/include/Inventor/draggers/SoPointLightDragger.h \
    lib/interaction/include/Inventor/draggers/SoRotateCylindricalDragger.h \
    lib/interaction/include/Inventor/draggers/SoRotateDiscDragger.h \
    lib/interaction/include/Inventor/draggers/SoRotateSphericalDragger.h \
    lib/interaction/include/Inventor/draggers/SoScale1Dragger.h \
    lib/interaction/include/Inventor/draggers/SoScale2Dragger.h \
    lib/interaction/include/Inventor/draggers/SoScale2UniformDragger.h \
    lib/interaction/include/Inventor/draggers/SoScaleUniformDragger.h \
    lib/interaction/include/Inventor/draggers/SoSpotLightDragger.h \
    lib/interaction/include/Inventor/draggers/SoTabBoxDragger.h \
    lib/interaction/include/Inventor/draggers/SoTabPlaneDragger.h \
    lib/interaction/include/Inventor/draggers/SoTrackballDragger.h \
    lib/interaction/include/Inventor/draggers/SoTransformBoxDragger.h \
    lib/interaction/include/Inventor/draggers/SoTransformerDragger.h \
    lib/interaction/include/Inventor/draggers/SoTranslate1Dragger.h \
    lib/interaction/include/Inventor/draggers/SoTranslate2Dragger.h \
    lib/interaction/include/Inventor/manips/SoCenterballManip.h \
    lib/interaction/include/Inventor/manips/SoDirectionalLightManip.h \
    lib/interaction/include/Inventor/manips/SoHandleBoxManip.h \
    lib/interaction/include/Inventor/manips/SoJackManip.h \
    lib/interaction/include/Inventor/manips/SoPointLightManip.h \
    lib/interaction/include/Inventor/manips/SoSpotLightManip.h \
    lib/interaction/include/Inventor/manips/SoTabBoxManip.h \
    lib/interaction/include/Inventor/manips/SoTrackballManip.h \
    lib/interaction/include/Inventor/manips/SoTransformBoxManip.h \
    lib/interaction/include/Inventor/manips/SoTransformManip.h \
    lib/interaction/include/Inventor/manips/SoTransformerManip.h \
    lib/interaction/include/Inventor/nodekits/SoInteractionKit.h \
    lib/interaction/include/Inventor/nodes/SoAntiSquish.h \
    lib/interaction/include/Inventor/nodes/SoSelection.h \
    lib/interaction/include/Inventor/nodes/SoSurroundScale.h \
    lib/interaction/src/draggers/geom/SoCenterballDraggerGeom.h \
    lib/interaction/src/draggers/geom/SoDirectionalLightDraggerGeom.h \
    lib/interaction/src/draggers/geom/SoDragPointDraggerGeom.h \
    lib/interaction/src/draggers/geom/SoHandleBoxDraggerGeom.h \
    lib/interaction/src/draggers/geom/SoJackDraggerGeom.h \
    lib/interaction/src/draggers/geom/SoPointLightDraggerGeom.h \
    lib/interaction/src/draggers/geom/SoRotateCylindricalDraggerGeom.h \
    lib/interaction/src/draggers/geom/SoRotateDiscDraggerGeom.h \
    lib/interaction/src/draggers/geom/SoRotateSphericalDraggerGeom.h \
    lib/interaction/src/draggers/geom/SoScale1DraggerGeom.h \
    lib/interaction/src/draggers/geom/SoScale2DraggerGeom.h \
    lib/interaction/src/draggers/geom/SoScale2UniformDraggerGeom.h \
    lib/interaction/src/draggers/geom/SoScaleUniformDraggerGeom.h \
    lib/interaction/src/draggers/geom/SoSpotLightDraggerGeom.h \
    lib/interaction/src/draggers/geom/SoTabBoxDraggerGeom.h \
    lib/interaction/src/draggers/geom/SoTabPlaneDraggerGeom.h \
    lib/interaction/src/draggers/geom/SoTrackballDraggerGeom.h \
    lib/interaction/src/draggers/geom/SoTransformBoxDraggerGeom.h \
    lib/interaction/src/draggers/geom/SoTransformerDraggerGeom.h \
    lib/interaction/src/draggers/geom/SoTranslate1DraggerGeom.h \
    lib/interaction/src/draggers/geom/SoTranslate2DraggerGeom.h \
    lib/nodekits/include/Inventor/SoNodeKitPath.h \
    lib/nodekits/include/Inventor/details/SoNodeKitDetail.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1AppearanceKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1BaseKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1CameraKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1ConeKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1CubeKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1CylinderKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1DirectionalLightKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1FaceSetKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1GroupKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1IndexedFaceSetKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1IndexedLineSetKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1IndexedNurbsCurveKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1IndexedNurbsSurfaceKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1IndexedTriangleMeshKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1LightKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1LineSetKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1NodeKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1NodekitCatalog.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1NodekitParts.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1NurbsCurveKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1NurbsSurfaceKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1OrthographicCameraKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1PerspectiveCameraKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1PointLightKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1PointSetKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1QuadMeshKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1SceneKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1ShapeKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1SphereKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1SpotLightKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1SubKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1Text2Kit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1Text3Kit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1TriangleStripSetKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1VertexShapeKit.h \
    lib/nodekits/include/Inventor/misc/upgraders/SoV1WrapperKit.h \
    lib/nodekits/include/Inventor/nodekits/SoAppearanceKit.h \
    lib/nodekits/include/Inventor/nodekits/SoBaseKit.h \
    lib/nodekits/include/Inventor/nodekits/SoCameraKit.h \
    lib/nodekits/include/Inventor/nodekits/SoLightKit.h \
    lib/nodekits/include/Inventor/nodekits/SoNodeKit.h \
    lib/nodekits/include/Inventor/nodekits/SoNodeKitListPart.h \
    lib/nodekits/include/Inventor/nodekits/SoNodekitCatalog.h \
    lib/nodekits/include/Inventor/nodekits/SoNodekitParts.h \
    lib/nodekits/include/Inventor/nodekits/SoSceneKit.h \
    lib/nodekits/include/Inventor/nodekits/SoSeparatorKit.h \
    lib/nodekits/include/Inventor/nodekits/SoShapeKit.h \
    lib/nodekits/include/Inventor/nodekits/SoSubKit.h \
    lib/nodekits/include/Inventor/nodekits/SoWrapperKit.h

PPSOURCES += \
    lib/database/src/so/nodes/SoCone.pp \
    lib/database/src/so/nodes/SoCube.pp \
    lib/database/src/so/nodes/SoCylinder.pp \
    lib/database/src/so/nodes/SoFaceSet.pp \
    lib/database/src/so/nodes/SoIndexedFaceSet.pp \
    lib/database/src/so/nodes/SoIndexedLineSet.pp \
    lib/database/src/so/nodes/SoIndexedTriangleStripSet.pp \
    lib/database/src/so/nodes/SoLineSet.pp \
    lib/database/src/so/nodes/SoPointSet.pp \
    lib/database/src/so/nodes/SoQuadMesh.pp \
    lib/database/src/so/nodes/SoSphere.pp \
    lib/database/src/so/nodes/SoTriangleStripSet.pp

YACCSOURCES = \
    lib/database/src/so/engines/SoCalcParse.y

SOURCES += \
    lib/database/src/sb/SbBox.c++ \
    lib/database/src/sb/SbColor.c++ \
    lib/database/src/sb/SbCylinder.c++ \
    lib/database/src/sb/SbDict.c++ \
    lib/database/src/sb/SbLine.c++ \
    lib/database/src/sb/SbMatrix.c++ \
    lib/database/src/sb/SbName.c++ \
    lib/database/src/sb/SbPList.c++ \
    lib/database/src/sb/SbPlane.c++ \
    lib/database/src/sb/SbRotation.c++ \
    lib/database/src/sb/SbSphere.c++ \
    lib/database/src/sb/SbString.c++ \
    lib/database/src/sb/SbTime.c++ \
    lib/database/src/sb/SbVec.c++ \
    lib/database/src/sb/SbView.c++ \
    lib/database/src/sb/SbViewportRegion.c++ \
    lib/database/src/sb/projectors/SbCylinderPlaneProjector.c++ \
    lib/database/src/sb/projectors/SbCylinderProjector.c++ \
    lib/database/src/sb/projectors/SbCylinderSectionProjector.c++ \
    lib/database/src/sb/projectors/SbCylinderSheetProjector.c++ \
    lib/database/src/sb/projectors/SbLineProjector.c++ \
    lib/database/src/sb/projectors/SbPlaneProjector.c++ \
    lib/database/src/sb/projectors/SbProjector.c++ \
    lib/database/src/sb/projectors/SbSpherePlaneProjector.c++ \
    lib/database/src/sb/projectors/SbSphereProjector.c++ \
    lib/database/src/sb/projectors/SbSphereSectionProjector.c++ \
    lib/database/src/sb/projectors/SbSphereSheetProjector.c++ \
    lib/database/src/so/SoAuditorList.c++ \
    lib/database/src/so/SoBase.c++ \
    lib/database/src/so/SoByteStream.c++ \
    lib/database/src/so/SoCBList.c++ \
    lib/database/src/so/SoChildList.c++ \
    lib/database/src/so/SoCompactPathList.c++ \
    lib/database/src/so/SoDB.c++ \
    lib/database/src/so/SoDebug.c++ \
    lib/database/src/so/SoInput.c++ \
    lib/database/src/so/SoLists.c++ \
    lib/database/src/so/SoNormalGenerator.c++ \
    lib/database/src/so/SoNotification.c++ \
    lib/database/src/so/SoOutput.c++ \
    lib/database/src/so/SoPath.c++ \
    lib/database/src/so/SoPickedPoint.c++ \
    lib/database/src/so/SoPrimitiveVertex.c++ \
    lib/database/src/so/SoState.c++ \
    lib/database/src/so/SoTempPath.c++ \
    lib/database/src/so/SoTranscribe.c++ \
    lib/database/src/so/SoType.c++ \
    lib/database/src/so/actions/SoAction.c++ \
    lib/database/src/so/actions/SoActionInit.c++ \
    lib/database/src/so/actions/SoCallbackAction.c++ \
    lib/database/src/so/actions/SoGLRenderAction.c++ \
    lib/database/src/so/actions/SoGetBoundingBoxAction.c++ \
    lib/database/src/so/actions/SoGetMatrixAction.c++ \
    lib/database/src/so/actions/SoHandleEventAction.c++ \
    lib/database/src/so/actions/SoPickAction.c++ \
    lib/database/src/so/actions/SoRayPickAction.c++ \
    lib/database/src/so/actions/SoSearchAction.c++ \
    lib/database/src/so/actions/SoWriteAction.c++ \
    lib/database/src/so/bundles/SoMaterialBundle.c++ \
    lib/database/src/so/bundles/SoNormalBundle.c++ \
    lib/database/src/so/bundles/SoTextureCoordinateBundle.c++ \
    lib/database/src/so/caches/SoBoundingBoxCache.c++ \
    lib/database/src/so/caches/SoCache.c++ \
    lib/database/src/so/caches/SoGLCacheList.c++ \
    lib/database/src/so/caches/SoGLRenderCache.c++ \
    lib/database/src/so/caches/SoNormalCache.c++ \
    lib/database/src/so/details/SoConeDetail.c++ \
    lib/database/src/so/details/SoCubeDetail.c++ \
    lib/database/src/so/details/SoCylinderDetail.c++ \
    lib/database/src/so/details/SoDetail.c++ \
    lib/database/src/so/details/SoDetailInit.c++ \
    lib/database/src/so/details/SoFaceDetail.c++ \
    lib/database/src/so/details/SoLineDetail.c++ \
    lib/database/src/so/details/SoPointDetail.c++ \
    lib/database/src/so/details/SoTextDetail.c++ \
    lib/database/src/so/elements/SoAccumulatedElement.c++ \
    lib/database/src/so/elements/SoAmbientColorElement.c++ \
    lib/database/src/so/elements/SoBBoxModelMatrixElement.c++ \
    lib/database/src/so/elements/SoCacheElement.c++ \
    lib/database/src/so/elements/SoClipPlaneElement.c++ \
    lib/database/src/so/elements/SoComplexityElement.c++ \
    lib/database/src/so/elements/SoComplexityTypeElement.c++ \
    lib/database/src/so/elements/SoCoordinateElement.c++ \
    lib/database/src/so/elements/SoCreaseAngleElement.c++ \
    lib/database/src/so/elements/SoDiffuseColorElement.c++ \
    lib/database/src/so/elements/SoDrawStyleElement.c++ \
    lib/database/src/so/elements/SoElement.c++ \
    lib/database/src/so/elements/SoElementInit.c++ \
    lib/database/src/so/elements/SoEmissiveColorElement.c++ \
    lib/database/src/so/elements/SoFloatElement.c++ \
    lib/database/src/so/elements/SoFocalDistanceElement.c++ \
    lib/database/src/so/elements/SoFontNameElement.c++ \
    lib/database/src/so/elements/SoFontSizeElement.c++ \
    lib/database/src/so/elements/SoGLAmbientColorElement.c++ \
    lib/database/src/so/elements/SoGLCacheContextElement.c++ \
    lib/database/src/so/elements/SoGLClipPlaneElement.c++ \
    lib/database/src/so/elements/SoGLCoordinateElement.c++ \
    lib/database/src/so/elements/SoGLDiffuseColorElement.c++ \
    lib/database/src/so/elements/SoGLDrawStyleElement.c++ \
    lib/database/src/so/elements/SoGLEmissiveColorElement.c++ \
    lib/database/src/so/elements/SoGLLazyElement.c++ \
    lib/database/src/so/elements/SoGLLightIdElement.c++ \
    lib/database/src/so/elements/SoGLLinePatternElement.c++ \
    lib/database/src/so/elements/SoGLLineWidthElement.c++ \
    lib/database/src/so/elements/SoGLModelMatrixElement.c++ \
    lib/database/src/so/elements/SoGLNormalElement.c++ \
    lib/database/src/so/elements/SoGLPointSizeElement.c++ \
    lib/database/src/so/elements/SoGLProjectionMatrixElement.c++ \
    lib/database/src/so/elements/SoGLRenderPassElement.c++ \
    lib/database/src/so/elements/SoGLShapeHintsElement.c++ \
    lib/database/src/so/elements/SoGLShininessElement.c++ \
    lib/database/src/so/elements/SoGLSpecularColorElement.c++ \
    lib/database/src/so/elements/SoGLTextureCoordinateElement.c++ \
    lib/database/src/so/elements/SoGLTextureEnabledElement.c++ \
    lib/database/src/so/elements/SoGLTextureImageElement.c++ \
    lib/database/src/so/elements/SoGLTextureMatrixElement.c++ \
    lib/database/src/so/elements/SoGLUpdateAreaElement.c++ \
    lib/database/src/so/elements/SoGLViewingMatrixElement.c++ \
    lib/database/src/so/elements/SoGLViewportRegionElement.c++ \
    lib/database/src/so/elements/SoInt32Element.c++ \
    lib/database/src/so/elements/SoLazyElement.c++ \
    lib/database/src/so/elements/SoLightAttenuationElement.c++ \
    lib/database/src/so/elements/SoLinePatternElement.c++ \
    lib/database/src/so/elements/SoLineWidthElement.c++ \
    lib/database/src/so/elements/SoLocalBBoxMatrixElement.c++ \
    lib/database/src/so/elements/SoMaterialBindingElement.c++ \
    lib/database/src/so/elements/SoModelMatrixElement.c++ \
    lib/database/src/so/elements/SoNormalBindingElement.c++ \
    lib/database/src/so/elements/SoNormalElement.c++ \
    lib/database/src/so/elements/SoOverrideElement.c++ \
    lib/database/src/so/elements/SoPickRayElement.c++ \
    lib/database/src/so/elements/SoPickStyleElement.c++ \
    lib/database/src/so/elements/SoPointSizeElement.c++ \
    lib/database/src/so/elements/SoProfileCoordinateElement.c++ \
    lib/database/src/so/elements/SoProfileElement.c++ \
    lib/database/src/so/elements/SoProjectionMatrixElement.c++ \
    lib/database/src/so/elements/SoReplacedElement.c++ \
    lib/database/src/so/elements/SoShapeHintsElement.c++ \
    lib/database/src/so/elements/SoShapeStyleElement.c++ \
    lib/database/src/so/elements/SoShininessElement.c++ \
    lib/database/src/so/elements/SoSpecularColorElement.c++ \
    lib/database/src/so/elements/SoSwitchElement.c++ \
    lib/database/src/so/elements/SoTextureCoordinateBindingElement.c++ \
    lib/database/src/so/elements/SoTextureCoordinateElement.c++ \
    lib/database/src/so/elements/SoTextureImageElement.c++ \
    lib/database/src/so/elements/SoTextureMatrixElement.c++ \
    lib/database/src/so/elements/SoTextureQualityElement.c++ \
    lib/database/src/so/elements/SoUnitsElement.c++ \
    lib/database/src/so/elements/SoViewVolumeElement.c++ \
    lib/database/src/so/elements/SoViewingMatrixElement.c++ \
    lib/database/src/so/elements/SoViewportRegionElement.c++ \
    lib/database/src/so/elements/SoWindowElement.c++ \
    lib/database/src/so/engines/SoBoolOperation.c++ \
    lib/database/src/so/engines/SoCalcExpr.c++ \
    lib/database/src/so/engines/SoCalculator.c++ \
    lib/database/src/so/engines/SoCompose.c++ \
    lib/database/src/so/engines/SoComputeBoundingBox.c++ \
    lib/database/src/so/engines/SoConcatenate.c++ \
    lib/database/src/so/engines/SoCounter.c++ \
    lib/database/src/so/engines/SoElapsedTime.c++ \
    lib/database/src/so/engines/SoEngine.c++ \
    lib/database/src/so/engines/SoEngineInit.c++ \
    lib/database/src/so/engines/SoFieldConverter.c++ \
    lib/database/src/so/engines/SoFieldConverters.c++ \
    lib/database/src/so/engines/SoGate.c++ \
    lib/database/src/so/engines/SoInterpolate.c++ \
    lib/database/src/so/engines/SoOnOff.c++ \
    lib/database/src/so/engines/SoOneShot.c++ \
    lib/database/src/so/engines/SoOutputData.c++ \
    lib/database/src/so/engines/SoSelectOne.c++ \
    lib/database/src/so/engines/SoTimeCounter.c++ \
    lib/database/src/so/engines/SoTransformVec3f.c++ \
    lib/database/src/so/engines/SoTriggerAny.c++ \
    lib/database/src/so/engines/SoUnknownEngine.c++ \
    lib/database/src/so/errors/SoDebugError.c++ \
    lib/database/src/so/errors/SoError.c++ \
    lib/database/src/so/errors/SoErrorInit.c++ \
    lib/database/src/so/errors/SoMemoryError.c++ \
    lib/database/src/so/errors/SoReadError.c++ \
    lib/database/src/so/events/SoButtonEvent.c++ \
    lib/database/src/so/events/SoEvent.c++ \
    lib/database/src/so/events/SoEventInit.c++ \
    lib/database/src/so/events/SoKeyboardEvent.c++ \
    lib/database/src/so/events/SoLocation2Event.c++ \
    lib/database/src/so/events/SoMotion3Event.c++ \
    lib/database/src/so/events/SoMouseButtonEvent.c++ \
    lib/database/src/so/events/SoSpaceballButtonEvent.c++ \
    lib/database/src/so/fields/SoField.c++ \
    lib/database/src/so/fields/SoFieldContainer.c++ \
    lib/database/src/so/fields/SoFieldData.c++ \
    lib/database/src/so/fields/SoFieldInit.c++ \
    lib/database/src/so/fields/SoGlobalField.c++ \
    lib/database/src/so/fields/SoMFBitMask.c++ \
    lib/database/src/so/fields/SoMFBool.c++ \
    lib/database/src/so/fields/SoMFColor.c++ \
    lib/database/src/so/fields/SoMFEngine.c++ \
    lib/database/src/so/fields/SoMFEnum.c++ \
    lib/database/src/so/fields/SoMFFloat.c++ \
    lib/database/src/so/fields/SoMFInt32.c++ \
    lib/database/src/so/fields/SoMFMatrix.c++ \
    lib/database/src/so/fields/SoMFName.c++ \
    lib/database/src/so/fields/SoMFNode.c++ \
    lib/database/src/so/fields/SoMFPath.c++ \
    lib/database/src/so/fields/SoMFPlane.c++ \
    lib/database/src/so/fields/SoMFRotation.c++ \
    lib/database/src/so/fields/SoMFShort.c++ \
    lib/database/src/so/fields/SoMFString.c++ \
    lib/database/src/so/fields/SoMFTime.c++ \
    lib/database/src/so/fields/SoMFUInt32.c++ \
    lib/database/src/so/fields/SoMFUShort.c++ \
    lib/database/src/so/fields/SoMFVec2f.c++ \
    lib/database/src/so/fields/SoMFVec3f.c++ \
    lib/database/src/so/fields/SoMFVec4f.c++ \
    lib/database/src/so/fields/SoSFBitMask.c++ \
    lib/database/src/so/fields/SoSFBool.c++ \
    lib/database/src/so/fields/SoSFColor.c++ \
    lib/database/src/so/fields/SoSFEngine.c++ \
    lib/database/src/so/fields/SoSFEnum.c++ \
    lib/database/src/so/fields/SoSFFloat.c++ \
    lib/database/src/so/fields/SoSFImage.c++ \
    lib/database/src/so/fields/SoSFInt32.c++ \
    lib/database/src/so/fields/SoSFMatrix.c++ \
    lib/database/src/so/fields/SoSFName.c++ \
    lib/database/src/so/fields/SoSFNode.c++ \
    lib/database/src/so/fields/SoSFPath.c++ \
    lib/database/src/so/fields/SoSFPlane.c++ \
    lib/database/src/so/fields/SoSFRotation.c++ \
    lib/database/src/so/fields/SoSFShort.c++ \
    lib/database/src/so/fields/SoSFString.c++ \
    lib/database/src/so/fields/SoSFTime.c++ \
    lib/database/src/so/fields/SoSFTrigger.c++ \
    lib/database/src/so/fields/SoSFUInt32.c++ \
    lib/database/src/so/fields/SoSFUShort.c++ \
    lib/database/src/so/fields/SoSFVec2f.c++ \
    lib/database/src/so/fields/SoSFVec3f.c++ \
    lib/database/src/so/fields/SoSFVec4f.c++ \
    lib/database/src/so/nodes/SoAnnotation.c++ \
    lib/database/src/so/nodes/SoArray.c++ \
    lib/database/src/so/nodes/SoAsciiText.c++ \
    lib/database/src/so/nodes/SoBaseColor.c++ \
    lib/database/src/so/nodes/SoBlinker.c++ \
    lib/database/src/so/nodes/SoCallback.c++ \
    lib/database/src/so/nodes/SoCamera.c++ \
    lib/database/src/so/nodes/SoClipPlane.c++ \
    lib/database/src/so/nodes/SoColorIndex.c++ \
    lib/database/src/so/nodes/SoComplexity.c++ \
    lib/database/src/so/nodes/SoCoordinate3.c++ \
    lib/database/src/so/nodes/SoCoordinate4.c++ \
    lib/database/src/so/nodes/SoDirectionalLight.c++ \
    lib/database/src/so/nodes/SoDrawStyle.c++ \
    lib/database/src/so/nodes/SoEnvironment.c++ \
    lib/database/src/so/nodes/SoEventCallback.c++ \
    lib/database/src/so/nodes/SoFile.c++ \
    lib/database/src/so/nodes/SoFont.c++ \
    lib/database/src/so/nodes/SoFontStyle.c++ \
    lib/database/src/so/nodes/SoGroup.c++ \
    lib/database/src/so/nodes/SoIndexedNurbsCurve.c++ \
    lib/database/src/so/nodes/SoIndexedNurbsSurface.c++ \
    lib/database/src/so/nodes/SoIndexedShape.c++ \
    lib/database/src/so/nodes/SoInfo.c++ \
    lib/database/src/so/nodes/SoLOD.c++ \
    lib/database/src/so/nodes/SoLabel.c++ \
    lib/database/src/so/nodes/SoLevelOfDetail.c++ \
    lib/database/src/so/nodes/SoLight.c++ \
    lib/database/src/so/nodes/SoLightModel.c++ \
    lib/database/src/so/nodes/SoLinearProfile.c++ \
    lib/database/src/so/nodes/SoLocateHighlight.c++ \
    lib/database/src/so/nodes/SoMaterial.c++ \
    lib/database/src/so/nodes/SoMaterialBinding.c++ \
    lib/database/src/so/nodes/SoMatrixTransform.c++ \
    lib/database/src/so/nodes/SoMultipleCopy.c++ \
    lib/database/src/so/nodes/SoNode.c++ \
    lib/database/src/so/nodes/SoNodeInit.c++ \
    lib/database/src/so/nodes/SoNonIndexedShape.c++ \
    lib/database/src/so/nodes/SoNormal.c++ \
    lib/database/src/so/nodes/SoNormalBinding.c++ \
    lib/database/src/so/nodes/SoNurbsCurve.c++ \
    lib/database/src/so/nodes/SoNurbsProfile.c++ \
    lib/database/src/so/nodes/SoNurbsSurface.c++ \
    lib/database/src/so/nodes/SoOrthographicCamera.c++ \
    lib/database/src/so/nodes/SoPackedColor.c++ \
    lib/database/src/so/nodes/SoPathSwitch.c++ \
    lib/database/src/so/nodes/SoPendulum.c++ \
    lib/database/src/so/nodes/SoPerspectiveCamera.c++ \
    lib/database/src/so/nodes/SoPickStyle.c++ \
    lib/database/src/so/nodes/SoPointLight.c++ \
    lib/database/src/so/nodes/SoProfile.c++ \
    lib/database/src/so/nodes/SoProfileCoordinate2.c++ \
    lib/database/src/so/nodes/SoProfileCoordinate3.c++ \
    lib/database/src/so/nodes/SoResetTransform.c++ \
    lib/database/src/so/nodes/SoRotation.c++ \
    lib/database/src/so/nodes/SoRotationXYZ.c++ \
    lib/database/src/so/nodes/SoRotor.c++ \
    lib/database/src/so/nodes/SoScale.c++ \
    lib/database/src/so/nodes/SoSeparator.c++ \
    lib/database/src/so/nodes/SoShape.c++ \
    lib/database/src/so/nodes/SoShapeHints.c++ \
    lib/database/src/so/nodes/SoShuttle.c++ \
    lib/database/src/so/nodes/SoSpotLight.c++ \
    lib/database/src/so/nodes/SoSwitch.c++ \
    lib/database/src/so/nodes/SoText2.c++ \
    lib/database/src/so/nodes/SoText3.c++ \
    lib/database/src/so/nodes/SoTexture2.c++ \
    lib/database/src/so/nodes/SoTexture2Transform.c++ \
    lib/database/src/so/nodes/SoTextureCoordinate2.c++ \
    lib/database/src/so/nodes/SoTextureCoordinateBinding.c++ \
    lib/database/src/so/nodes/SoTextureCoordinateDefault.c++ \
    lib/database/src/so/nodes/SoTextureCoordinateEnvironment.c++ \
    lib/database/src/so/nodes/SoTextureCoordinateFunction.c++ \
    lib/database/src/so/nodes/SoTextureCoordinatePlane.c++ \
    lib/database/src/so/nodes/SoTransform.c++ \
    lib/database/src/so/nodes/SoTransformSeparator.c++ \
    lib/database/src/so/nodes/SoTransformation.c++ \
    lib/database/src/so/nodes/SoTranslation.c++ \
    lib/database/src/so/nodes/SoUnits.c++ \
    lib/database/src/so/nodes/SoUnknownNode.c++ \
    lib/database/src/so/nodes/SoVertexArray.c++ \
    lib/database/src/so/nodes/SoVertexProperty.c++ \
    lib/database/src/so/nodes/SoVertexShape.c++ \
    lib/database/src/so/nodes/SoWWWAnchor.c++ \
    lib/database/src/so/nodes/SoWWWInline.c++ \
    lib/database/src/so/nodes/nurbs/SoCurveMaps.c++ \
    lib/database/src/so/nodes/nurbs/SoCurveRender.c++ \
    lib/database/src/so/nodes/nurbs/SoCurveRndEvl.c++ \
    lib/database/src/so/nodes/nurbs/SoGLRender.c++ \
    lib/database/src/so/nodes/nurbs/SoPickEvals.c++ \
    lib/database/src/so/nodes/nurbs/SoPickMaps.c++ \
    lib/database/src/so/nodes/nurbs/SoPickRender.c++ \
    lib/database/src/so/nodes/nurbs/SoPrimEvals.c++ \
    lib/database/src/so/nodes/nurbs/SoPrimMaps.c++ \
    lib/database/src/so/nodes/nurbs/SoPrimRender.c++ \
    lib/database/src/so/nodes/nurbs/clients/nurbsClient.c++ \
    lib/database/src/so/nodes/nurbs/libnurbs/libNurbs.c++ \
    lib/database/src/so/sensors/SoAlarmSensor.c++ \
    lib/database/src/so/sensors/SoDataSensor.c++ \
    lib/database/src/so/sensors/SoDelayQueueSensor.c++ \
    lib/database/src/so/sensors/SoFieldSensor.c++ \
    lib/database/src/so/sensors/SoIdleSensor.c++ \
    lib/database/src/so/sensors/SoNodeSensor.c++ \
    lib/database/src/so/sensors/SoOneShotSensor.c++ \
    lib/database/src/so/sensors/SoPathSensor.c++ \
    lib/database/src/so/sensors/SoSensor.c++ \
    lib/database/src/so/sensors/SoSensorMgr.c++ \
    lib/database/src/so/sensors/SoTimerQueueSensor.c++ \
    lib/database/src/so/sensors/SoTimerSensor.c++ \
    lib/database/src/so/upgraders/SoUpgrader.c++ \
    lib/database/src/so/upgraders/SoUpgraderInit.c++ \
    lib/database/src/so/upgraders/SoV1CustomNode.c++ \
    lib/database/src/so/upgraders/SoV1DrawStyle.c++ \
    lib/database/src/so/upgraders/SoV1Environment.c++ \
    lib/database/src/so/upgraders/SoV1IndexedTriangleMesh.c++ \
    lib/database/src/so/upgraders/SoV1LayerGroup.c++ \
    lib/database/src/so/upgraders/SoV1LightModel.c++ \
    lib/database/src/so/upgraders/SoV1Material.c++ \
    lib/database/src/so/upgraders/SoV1PackedColor.c++ \
    lib/database/src/so/upgraders/SoV1PickStyle.c++ \
    lib/database/src/so/upgraders/SoV1Separator.c++ \
    lib/database/src/so/upgraders/SoV1ShapeHints.c++ \
    lib/database/src/so/upgraders/SoV1Text2.c++ \
    lib/database/src/so/upgraders/SoV1Text3.c++ \
    lib/database/src/so/upgraders/SoV1Texture2.c++ \
    lib/database/src/so/upgraders/SoV1TextureCoordinateCube.c++ \
    lib/database/src/so/upgraders/SoV1TextureCoordinateCylinder.c++ \
    lib/database/src/so/upgraders/SoV1TextureCoordinateEnvironment.c++ \
    lib/database/src/so/upgraders/SoV1TextureCoordinatePlane.c++ \
    lib/database/src/so/upgraders/SoV1TextureCoordinateSphere.c++ \
    lib/database/src/so/upgraders/SoV2AsciiText.c++ \
    lib/database/src/so/upgraders/SoV2FontStyle.c++ \
    lib/database/src/so/upgraders/SoV2LOD.c++ \
    lib/database/src/so/upgraders/SoV2MaterialIndex.c++ \
    lib/database/src/so/upgraders/SoV2Text2.c++ \
    lib/database/src/so/upgraders/SoV2Text3.c++ \
    lib/database/src/so/upgraders/SoV2VertexProperty.c++ \
    lib/database/src/so/upgraders/SoV2WWWAnchor.c++ \
    lib/database/src/so/upgraders/SoV2WWWInline.c++ \
    lib/database/src/so/linux.c++ \
    lib/interaction/src/SoInteraction.c++ \
    lib/interaction/src/SoSceneMgr.c++ \
    lib/interaction/src/SoSelection.c++ \
    lib/interaction/src/actions/SoBoxHL.c++ \
    lib/interaction/src/actions/SoLineHL.c++ \
    lib/interaction/src/draggers/SoCenterballDragger.c++ \
    lib/interaction/src/draggers/SoDirectionalLightDragger.c++ \
    lib/interaction/src/draggers/SoDragPointDragger.c++ \
    lib/interaction/src/draggers/SoDragger.c++ \
    lib/interaction/src/draggers/SoDraggerInit.c++ \
    lib/interaction/src/draggers/SoHandleBoxDragger.c++ \
    lib/interaction/src/draggers/SoJackDragger.c++ \
    lib/interaction/src/draggers/SoPointLightDragger.c++ \
    lib/interaction/src/draggers/SoRotateCylindricalDragger.c++ \
    lib/interaction/src/draggers/SoRotateDiscDragger.c++ \
    lib/interaction/src/draggers/SoRotateSphericalDragger.c++ \
    lib/interaction/src/draggers/SoScale1Dragger.c++ \
    lib/interaction/src/draggers/SoScale2Dragger.c++ \
    lib/interaction/src/draggers/SoScale2UniformDragger.c++ \
    lib/interaction/src/draggers/SoScaleUniformDragger.c++ \
    lib/interaction/src/draggers/SoSpotLightDragger.c++ \
    lib/interaction/src/draggers/SoTabBoxDragger.c++ \
    lib/interaction/src/draggers/SoTabPlaneDragger.c++ \
    lib/interaction/src/draggers/SoTrackballDragger.c++ \
    lib/interaction/src/draggers/SoTransformBoxDragger.c++ \
    lib/interaction/src/draggers/SoTransformerDragger.c++ \
    lib/interaction/src/draggers/SoTranslate1Dragger.c++ \
    lib/interaction/src/draggers/SoTranslate2Dragger.c++ \
    lib/interaction/src/manips/SoCenterballManip.c++ \
    lib/interaction/src/manips/SoDirLtManip.c++ \
    lib/interaction/src/manips/SoHbox.c++ \
    lib/interaction/src/manips/SoJackManip.c++ \
    lib/interaction/src/manips/SoPtLtManip.c++ \
    lib/interaction/src/manips/SoSpotLtManip.c++ \
    lib/interaction/src/manips/SoTabBoxManip.c++ \
    lib/interaction/src/manips/SoTball.c++ \
    lib/interaction/src/manips/SoTransformManip.c++ \
    lib/interaction/src/manips/SoTransformerManip.c++ \
    lib/interaction/src/manips/SoXformBox.c++ \
    lib/interaction/src/nodekits/SoInteractionKit.c++ \
    lib/interaction/src/nodes/SoAntiSquish.c++ \
    lib/interaction/src/nodes/SoSurroundScale.c++ \
    lib/nodekits/src/SoNodeKitPath.c++ \
    lib/nodekits/src/details/SoNodeKitDetail.c++ \
    lib/nodekits/src/nodekits/SoAppearKit.c++ \
    lib/nodekits/src/nodekits/SoBaseKit.c++ \
    lib/nodekits/src/nodekits/SoCameraKit.c++ \
    lib/nodekits/src/nodekits/SoLightKit.c++ \
    lib/nodekits/src/nodekits/SoNkCatalog.c++ \
    lib/nodekits/src/nodekits/SoNkParts.c++ \
    lib/nodekits/src/nodekits/SoNodeKit.c++ \
    lib/nodekits/src/nodekits/SoNodeKitListPart.c++ \
    lib/nodekits/src/nodekits/SoSceneKit.c++ \
    lib/nodekits/src/nodekits/SoSeparatorKit.c++ \
    lib/nodekits/src/nodekits/SoShapeKit.c++ \
    lib/nodekits/src/nodekits/SoWrapperKit.c++ \
    lib/nodekits/src/upgraders/SoV1AppearKit.c++ \
    lib/nodekits/src/upgraders/SoV1BaseKit.c++ \
    lib/nodekits/src/upgraders/SoV1CameraKit.c++ \
    lib/nodekits/src/upgraders/SoV1ConeKit.c++ \
    lib/nodekits/src/upgraders/SoV1CubeKit.c++ \
    lib/nodekits/src/upgraders/SoV1CylinderKit.c++ \
    lib/nodekits/src/upgraders/SoV1DirLtKit.c++ \
    lib/nodekits/src/upgraders/SoV1FaceSetKit.c++ \
    lib/nodekits/src/upgraders/SoV1GroupKit.c++ \
    lib/nodekits/src/upgraders/SoV1IFaceSetKit.c++ \
    lib/nodekits/src/upgraders/SoV1ILineSetKit.c++ \
    lib/nodekits/src/upgraders/SoV1INrbCurvKit.c++ \
    lib/nodekits/src/upgraders/SoV1INrbSurfKit.c++ \
    lib/nodekits/src/upgraders/SoV1ITMshSetKit.c++ \
    lib/nodekits/src/upgraders/SoV1LightKit.c++ \
    lib/nodekits/src/upgraders/SoV1LineSetKit.c++ \
    lib/nodekits/src/upgraders/SoV1NkCatalog.c++ \
    lib/nodekits/src/upgraders/SoV1NkParts.c++ \
    lib/nodekits/src/upgraders/SoV1NodeKit.c++ \
    lib/nodekits/src/upgraders/SoV1NurbCurvKit.c++ \
    lib/nodekits/src/upgraders/SoV1NurbSurfKit.c++ \
    lib/nodekits/src/upgraders/SoV1OrthoCamKit.c++ \
    lib/nodekits/src/upgraders/SoV1PerspCamKit.c++ \
    lib/nodekits/src/upgraders/SoV1PointLtKit.c++ \
    lib/nodekits/src/upgraders/SoV1PointSetKit.c++ \
    lib/nodekits/src/upgraders/SoV1QuadMeshKit.c++ \
    lib/nodekits/src/upgraders/SoV1SceneKit.c++ \
    lib/nodekits/src/upgraders/SoV1ShapeKit.c++ \
    lib/nodekits/src/upgraders/SoV1SphereKit.c++ \
    lib/nodekits/src/upgraders/SoV1SpotLtKit.c++ \
    lib/nodekits/src/upgraders/SoV1Text2Kit.c++ \
    lib/nodekits/src/upgraders/SoV1Text3Kit.c++ \
    lib/nodekits/src/upgraders/SoV1TriStripKit.c++ \
    lib/nodekits/src/upgraders/SoV1VtxShapeKit.c++ \
    lib/nodekits/src/upgraders/SoV1WrapperKit.c++

# PPP Generated sources
SOURCES += \
    lib/database/src/so/nodes/SoCone.c++ \
    lib/database/src/so/nodes/SoCube.c++ \
    lib/database/src/so/nodes/SoCylinder.c++ \
    lib/database/src/so/nodes/SoFaceSet.c++ \
    lib/database/src/so/nodes/SoIndexedFaceSet.c++ \
    lib/database/src/so/nodes/SoIndexedLineSet.c++ \
    lib/database/src/so/nodes/SoIndexedTriangleStripSet.c++ \
    lib/database/src/so/nodes/SoLineSet.c++ \
    lib/database/src/so/nodes/SoPointSet.c++ \
    lib/database/src/so/nodes/SoQuadMesh.c++ \
    lib/database/src/so/nodes/SoSphere.c++ \
    lib/database/src/so/nodes/SoTriangleStripSet.c++

# image loaders
SOURCES += \
    lib/database/src/so/nodes/readGIF.c

RELATEDFILES += \
    lib/database/src/so/nodes/SoCone.pp \
    lib/database/src/so/nodes/SoCube.pp \
    lib/database/src/so/nodes/SoCylinder.pp \
    lib/database/src/so/nodes/SoFaceSet.pp \
    lib/database/src/so/nodes/SoIndexedFaceSet.pp \
    lib/database/src/so/nodes/SoIndexedLineSet.pp \
    lib/database/src/so/nodes/SoIndexedTriangleStripSet.pp \
    lib/database/src/so/nodes/SoLineSet.pp \
    lib/database/src/so/nodes/SoPointSet.pp \
    lib/database/src/so/nodes/SoQuadMesh.pp \
    lib/database/src/so/nodes/SoSphere.pp \
    lib/database/src/so/nodes/SoTriangleStripSet.pp    

win32::SOURCES += \
    lib/initDll.c++

win32::RC_FILE += \
    lib/resource.rc

# mac framework config
macx::lib_bundle {
  QMAKE_FRAMEWORK_BUNDLE_NAME = Inventor
  QMAKE_FRAMEWORK_VERSION = 2.4.0
    
  FRAMEWORK_PRIVHEADERS1.version = Versions
  FRAMEWORK_PRIVHEADERS1.path = PrivateHeaders
  FRAMEWORK_PRIVHEADERS1.files = \
    lib/database/include/SoDebug.h \
    lib/database/include/SoUnknownEngine.h \
    lib/database/include/SoUnknownNode.h
  QMAKE_BUNDLE_DATA += FRAMEWORK_PRIVHEADERS1

  FRAMEWORK_HEADERS1.version = Versions
  FRAMEWORK_HEADERS1.path = Headers
  FRAMEWORK_HEADERS1.files = \
    lib/database/include/Inventor/SoOffscreenRenderer.h \
  # QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS1

  FRAMEWORK_HEADERS2.version = Versions
  FRAMEWORK_HEADERS2.path = Headers
  FRAMEWORK_HEADERS2.files = \
    lib/mevis/include/Inventor/SoCatch.h \
    lib/mevis/include/Inventor/SoInventor.h \
    lib/mevis/include/Inventor/SoMeVis.h \
    lib/mevis/include/Inventor/SoTrace.h \
    lib/database/include/Inventor/Sb.h \
    lib/database/include/Inventor/SbBasic.h \
    lib/database/include/Inventor/SbBox.h \
    lib/database/include/Inventor/SbColor.h \
    lib/database/include/Inventor/SbDict.h \
    lib/database/include/Inventor/SbLinear.h \
    lib/database/include/Inventor/SbPList.h \
    lib/database/include/Inventor/SbString.h \
    lib/database/include/Inventor/SbTime.h \
    lib/database/include/Inventor/SbViewportRegion.h \
    lib/database/include/Inventor/So.h \
    lib/database/include/Inventor/SoDB.h \
    lib/database/include/Inventor/SoInput.h \
    lib/database/include/Inventor/SoLists.h \
    lib/database/include/Inventor/SoOffscreenRenderer.h \
    lib/database/include/Inventor/SoOutput.h \
    lib/database/include/Inventor/SoPath.h \
    lib/database/include/Inventor/SoPickedPoint.h \
    lib/database/include/Inventor/SoPrimitiveVertex.h \
    lib/database/include/Inventor/SoType.h \
    lib/interaction/include/Inventor/SoInteraction.h \
    lib/interaction/include/Inventor/SoSceneManager.h \
    lib/nodekits/include/Inventor/SoNodeKitPath.h
  QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS2

  FRAMEWORK_HEADERS3.path = Headers/actions
  FRAMEWORK_HEADERS3.files = \
    lib/database/include/Inventor/actions/SoAction.h \
    lib/database/include/Inventor/actions/SoActions.h \
    lib/database/include/Inventor/actions/SoCallbackAction.h \
    lib/database/include/Inventor/actions/SoGetBoundingBoxAction.h \
    lib/database/include/Inventor/actions/SoGetMatrixAction.h \
    lib/database/include/Inventor/actions/SoGLRenderAction.h \
    lib/database/include/Inventor/actions/SoHandleEventAction.h \
    lib/database/include/Inventor/actions/SoPickAction.h \
    lib/database/include/Inventor/actions/SoRayPickAction.h \
    lib/database/include/Inventor/actions/SoSearchAction.h \
    lib/database/include/Inventor/actions/SoSubAction.h \
    lib/database/include/Inventor/actions/SoWriteAction.h \
    lib/interaction/include/Inventor/actions/SoBoxHighlightRenderAction.h \
    lib/interaction/include/Inventor/actions/SoLineHighlightRenderAction.h
  QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS3

  FRAMEWORK_HEADERS4.path = Headers/bundles
  FRAMEWORK_HEADERS4.files = \
    lib/database/include/Inventor/bundles/SoBundle.h \
    lib/database/include/Inventor/bundles/SoMaterialBundle.h \
    lib/database/include/Inventor/bundles/SoNormalBundle.h \
    lib/database/include/Inventor/bundles/SoTextureCoordinateBundle.h
  QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS4

  FRAMEWORK_HEADERS5.path = Headers/caches
  FRAMEWORK_HEADERS5.files = \
    lib/database/include/Inventor/caches/SoBoundingBoxCache.h \
    lib/database/include/Inventor/caches/SoCache.h \
    lib/database/include/Inventor/caches/SoGLCacheList.h \
    lib/database/include/Inventor/caches/SoGLRenderCache.h \
    lib/database/include/Inventor/caches/SoNormalCache.h
  QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS5

  FRAMEWORK_HEADERS6.path = Headers/details
  FRAMEWORK_HEADERS6.files = \
    lib/database/include/Inventor/details/SoConeDetail.h \
    lib/database/include/Inventor/details/SoCubeDetail.h \
    lib/database/include/Inventor/details/SoCylinderDetail.h \
    lib/database/include/Inventor/details/SoDetail.h \
    lib/database/include/Inventor/details/SoDetails.h \
    lib/database/include/Inventor/details/SoFaceDetail.h \
    lib/database/include/Inventor/details/SoLineDetail.h \
    lib/database/include/Inventor/details/SoPointDetail.h \
    lib/database/include/Inventor/details/SoSubDetail.h \
    lib/database/include/Inventor/details/SoTextDetail.h \
    lib/nodekits/include/Inventor/details/SoNodeKitDetail.h
  QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS6

  FRAMEWORK_HEADERS7.path = Headers/draggers
  FRAMEWORK_HEADERS7.files = \
    lib/interaction/include/Inventor/draggers/SoRotateSphericalDragger.h \
    lib/interaction/include/Inventor/draggers/SoCenterballDragger.h \
    lib/interaction/include/Inventor/draggers/SoDirectionalLightDragger.h \
    lib/interaction/include/Inventor/draggers/SoDragger.h \
    lib/interaction/include/Inventor/draggers/SoDragPointDragger.h \
    lib/interaction/include/Inventor/draggers/SoHandleBoxDragger.h \
    lib/interaction/include/Inventor/draggers/SoJackDragger.h \
    lib/interaction/include/Inventor/draggers/SoPointLightDragger.h \
    lib/interaction/include/Inventor/draggers/SoRotateCylindricalDragger.h \
    lib/interaction/include/Inventor/draggers/SoRotateDiscDragger.h \
    lib/interaction/include/Inventor/draggers/SoScale1Dragger.h \
    lib/interaction/include/Inventor/draggers/SoScale2Dragger.h \
    lib/interaction/include/Inventor/draggers/SoScale2UniformDragger.h \
    lib/interaction/include/Inventor/draggers/SoScaleUniformDragger.h \
    lib/interaction/include/Inventor/draggers/SoSpotLightDragger.h \
    lib/interaction/include/Inventor/draggers/SoTabBoxDragger.h \
    lib/interaction/include/Inventor/draggers/SoTabPlaneDragger.h \
    lib/interaction/include/Inventor/draggers/SoTrackballDragger.h \
    lib/interaction/include/Inventor/draggers/SoTransformBoxDragger.h \
    lib/interaction/include/Inventor/draggers/SoTransformerDragger.h \
    lib/interaction/include/Inventor/draggers/SoTranslate1Dragger.h \
    lib/interaction/include/Inventor/draggers/SoTranslate2Dragger.h
  QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS7

  FRAMEWORK_HEADERS8.path = Headers/elements
  FRAMEWORK_HEADERS8.files = \
    lib/mevis/include/Inventor/elements/SoGLPolygonOffsetElement.h \
    lib/mevis/include/Inventor/elements/SoGLStencilBitsElement.h \
    lib/mevis/include/Inventor/elements/SoPolygonOffsetElement.h \
    lib/mevis/include/Inventor/elements/SoStencilBitsElement.h \
    lib/database/include/Inventor/elements/SoAccumulatedElement.h \
    lib/database/include/Inventor/elements/SoAmbientColorElement.h \
    lib/database/include/Inventor/elements/SoBBoxModelMatrixElement.h \
    lib/database/include/Inventor/elements/SoCacheElement.h \
    lib/database/include/Inventor/elements/SoClipPlaneElement.h \
    lib/database/include/Inventor/elements/SoComplexityElement.h \
    lib/database/include/Inventor/elements/SoComplexityTypeElement.h \
    lib/database/include/Inventor/elements/SoCoordinateElement.h \
    lib/database/include/Inventor/elements/SoCreaseAngleElement.h \
    lib/database/include/Inventor/elements/SoCullVolumeElement.h \
    lib/database/include/Inventor/elements/SoCurrentGLMaterialElement.h \
    lib/database/include/Inventor/elements/SoDiffuseColorElement.h \
    lib/database/include/Inventor/elements/SoDrawStyleElement.h \
    lib/database/include/Inventor/elements/SoElement.h \
    lib/database/include/Inventor/elements/SoElements.h \
    lib/database/include/Inventor/elements/SoEmissiveColorElement.h \
    lib/database/include/Inventor/elements/SoFloatElement.h \
    lib/database/include/Inventor/elements/SoFocalDistanceElement.h \
    lib/database/include/Inventor/elements/SoFontNameElement.h \
    lib/database/include/Inventor/elements/SoFontSizeElement.h \
    lib/database/include/Inventor/elements/SoGLAmbientColorElement.h \
    lib/database/include/Inventor/elements/SoGLCacheContextElement.h \
    lib/database/include/Inventor/elements/SoGLClipPlaneElement.h \
    lib/database/include/Inventor/elements/SoGLColorIndexElement.h \
    lib/database/include/Inventor/elements/SoGLCoordinateElement.h \
    lib/database/include/Inventor/elements/SoGLDiffuseColorElement.h \
    lib/database/include/Inventor/elements/SoGLDrawStyleElement.h \
    lib/database/include/Inventor/elements/SoGLEmissiveColorElement.h \
    lib/database/include/Inventor/elements/SoGLLazyElement.h \
    lib/database/include/Inventor/elements/SoGLLightIdElement.h \
    lib/database/include/Inventor/elements/SoGLLightModelElement.h \
    lib/database/include/Inventor/elements/SoGLLinePatternElement.h \
    lib/database/include/Inventor/elements/SoGLLineWidthElement.h \
    lib/database/include/Inventor/elements/SoGLModelMatrixElement.h \
    lib/database/include/Inventor/elements/SoGLNormalElement.h \
    lib/database/include/Inventor/elements/SoGLPointSizeElement.h \
    lib/database/include/Inventor/elements/SoGLPolygonStippleElement.h \
    lib/database/include/Inventor/elements/SoGLProjectionMatrixElement.h \
    lib/database/include/Inventor/elements/SoGLRenderPassElement.h \
    lib/database/include/Inventor/elements/SoGLShapeHintsElement.h \
    lib/database/include/Inventor/elements/SoGLShininessElement.h \
    lib/database/include/Inventor/elements/SoGLSpecularColorElement.h \
    lib/database/include/Inventor/elements/SoGLTextureBlendColorElement.h \
    lib/database/include/Inventor/elements/SoGLTextureCoordinateElement.h \
    lib/database/include/Inventor/elements/SoGLTextureEnabledElement.h \
    lib/database/include/Inventor/elements/SoGLTextureImageElement.h \
    lib/database/include/Inventor/elements/SoGLTextureMatrixElement.h \
    lib/database/include/Inventor/elements/SoGLTextureModelElement.h \
    lib/database/include/Inventor/elements/SoGLTextureQualityElement.h \
    lib/database/include/Inventor/elements/SoGLTextureWrapSElement.h \
    lib/database/include/Inventor/elements/SoGLTextureWrapTElement.h \
    lib/database/include/Inventor/elements/SoGLUpdateAreaElement.h \
    lib/database/include/Inventor/elements/SoGLViewingMatrixElement.h \
    lib/database/include/Inventor/elements/SoGLViewportRegionElement.h \
    lib/database/include/Inventor/elements/SoInt32Element.h \
    lib/database/include/Inventor/elements/SoLazyElement.h \
    lib/database/include/Inventor/elements/SoLightAttenuationElement.h \
    lib/database/include/Inventor/elements/SoLightModelElement.h \
    lib/database/include/Inventor/elements/SoLinePatternElement.h \
    lib/database/include/Inventor/elements/SoLineWidthElement.h \
    lib/database/include/Inventor/elements/SoLocalBBoxMatrixElement.h \
    lib/database/include/Inventor/elements/SoLongElement.h \
    lib/database/include/Inventor/elements/SoMaterialBindingElement.h \
    lib/database/include/Inventor/elements/SoModelMatrixElement.h \
    lib/database/include/Inventor/elements/SoNormalBindingElement.h \
    lib/database/include/Inventor/elements/SoNormalElement.h \
    lib/database/include/Inventor/elements/SoOverrideElement.h \
    lib/database/include/Inventor/elements/SoPickRayElement.h \
    lib/database/include/Inventor/elements/SoPickStyleElement.h \
    lib/database/include/Inventor/elements/SoPointSizeElement.h \
    lib/database/include/Inventor/elements/SoProfileCoordinateElement.h \
    lib/database/include/Inventor/elements/SoProfileElement.h \
    lib/database/include/Inventor/elements/SoProjectionMatrixElement.h \
    lib/database/include/Inventor/elements/SoReplacedElement.h \
    lib/database/include/Inventor/elements/SoShapeHintsElement.h \
    lib/database/include/Inventor/elements/SoShapeStyleElement.h \
    lib/database/include/Inventor/elements/SoShininessElement.h \
    lib/database/include/Inventor/elements/SoSpecularColorElement.h \
    lib/database/include/Inventor/elements/SoSubElement.h \
    lib/database/include/Inventor/elements/SoSwitchElement.h \
    lib/database/include/Inventor/elements/SoTextureBlendColorElement.h \
    lib/database/include/Inventor/elements/SoTextureCoordinateBindingElement.h \
    lib/database/include/Inventor/elements/SoTextureCoordinateElement.h \
    lib/database/include/Inventor/elements/SoTextureImageElement.h \
    lib/database/include/Inventor/elements/SoTextureMatrixElement.h \
    lib/database/include/Inventor/elements/SoTextureModelElement.h \
    lib/database/include/Inventor/elements/SoTextureQualityElement.h \
    lib/database/include/Inventor/elements/SoTextureWrapSElement.h \
    lib/database/include/Inventor/elements/SoTextureWrapTElement.h \
    lib/database/include/Inventor/elements/SoTransparencyElement.h \
    lib/database/include/Inventor/elements/SoUnitsElement.h \
    lib/database/include/Inventor/elements/SoViewVolumeElement.h \
    lib/database/include/Inventor/elements/SoViewingMatrixElement.h \
    lib/database/include/Inventor/elements/SoViewportRegionElement.h \
    lib/database/include/Inventor/elements/SoWindowElement.h
  QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS8

  FRAMEWORK_HEADERS9.path = Headers/engines
  FRAMEWORK_HEADERS9.files = \
    lib/database/include/Inventor/engines/SoBoolOperation.h \
    lib/database/include/Inventor/engines/SoCalculator.h \
    lib/database/include/Inventor/engines/SoCompose.h \
    lib/database/include/Inventor/engines/SoComputeBoundingBox.h \
    lib/database/include/Inventor/engines/SoConcatenate.h \
    lib/database/include/Inventor/engines/SoCounter.h \
    lib/database/include/Inventor/engines/SoElapsedTime.h \
    lib/database/include/Inventor/engines/SoEngine.h \
    lib/database/include/Inventor/engines/SoEngines.h \
    lib/database/include/Inventor/engines/SoFieldConverter.h \
    lib/database/include/Inventor/engines/SoGate.h \
    lib/database/include/Inventor/engines/SoInterpolate.h \
    lib/database/include/Inventor/engines/SoOneShot.h \
    lib/database/include/Inventor/engines/SoOnOff.h \
    lib/database/include/Inventor/engines/SoOutputData.h \
    lib/database/include/Inventor/engines/SoSelectOne.h \
    lib/database/include/Inventor/engines/SoSubEngine.h \
    lib/database/include/Inventor/engines/SoTimeCounter.h \
    lib/database/include/Inventor/engines/SoTransformVec3f.h \
    lib/database/include/Inventor/engines/SoTriggerAny.h
  QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS9

  FRAMEWORK_HEADERS10.path = Headers/errors
  FRAMEWORK_HEADERS10.files = \
    lib/database/include/Inventor/errors/SoDebugError.h \
    lib/database/include/Inventor/errors/SoError.h \
    lib/database/include/Inventor/errors/SoErrors.h \
    lib/database/include/Inventor/errors/SoMemoryError.h \
    lib/database/include/Inventor/errors/SoReadError.h
  QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS10

  FRAMEWORK_HEADERS11.path = Headers/events
  FRAMEWORK_HEADERS11.files = \
    lib/database/include/Inventor/events/SoButtonEvent.h \
    lib/database/include/Inventor/events/SoEvent.h \
    lib/database/include/Inventor/events/SoEvents.h \
    lib/database/include/Inventor/events/SoKeyboardEvent.h \
    lib/database/include/Inventor/events/SoLocation2Event.h \
    lib/database/include/Inventor/events/SoMotion3Event.h \
    lib/database/include/Inventor/events/SoMouseButtonEvent.h \
    lib/database/include/Inventor/events/SoSpaceballButtonEvent.h \
    lib/database/include/Inventor/events/SoSubEvent.h
  QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS11

  FRAMEWORK_HEADERS12.path = Headers/fields
  FRAMEWORK_HEADERS12.files = \
    lib/mevis/include/Inventor/fields/SoSFVec2s.h \
    lib/mevis/include/Inventor/fields/SoSFVec3s.h \
    lib/database/include/Inventor/fields/SoMFLong.h \
    lib/database/include/Inventor/fields/SoMFUShort.h \
    lib/database/include/Inventor/fields/SoSFInt32.h \
    lib/database/include/Inventor/fields/SoField.h \
    lib/database/include/Inventor/fields/SoFieldContainer.h \
    lib/database/include/Inventor/fields/SoFieldData.h \
    lib/database/include/Inventor/fields/SoFields.h \
    lib/database/include/Inventor/fields/SoMFBitMask.h \
    lib/database/include/Inventor/fields/SoMFBool.h \
    lib/database/include/Inventor/fields/SoMFColor.h \
    lib/database/include/Inventor/fields/SoMFEngine.h \
    lib/database/include/Inventor/fields/SoMFEnum.h \
    lib/database/include/Inventor/fields/SoMFFloat.h \
    lib/database/include/Inventor/fields/SoMFInt32.h \
    lib/database/include/Inventor/fields/SoMFMatrix.h \
    lib/database/include/Inventor/fields/SoMFName.h \
    lib/database/include/Inventor/fields/SoMFNode.h \
    lib/database/include/Inventor/fields/SoMFPath.h \
    lib/database/include/Inventor/fields/SoMFPlane.h \
    lib/database/include/Inventor/fields/SoMFRotation.h \
    lib/database/include/Inventor/fields/SoMFShort.h \
    lib/database/include/Inventor/fields/SoMFString.h \
    lib/database/include/Inventor/fields/SoMFTime.h \
    lib/database/include/Inventor/fields/SoMFUInt32.h \
    lib/database/include/Inventor/fields/SoMFULong.h \
    lib/database/include/Inventor/fields/SoMFVec2f.h \
    lib/database/include/Inventor/fields/SoMFVec3f.h \
    lib/database/include/Inventor/fields/SoMFVec4f.h \
    lib/database/include/Inventor/fields/SoSFBitMask.h \
    lib/database/include/Inventor/fields/SoSFBool.h \
    lib/database/include/Inventor/fields/SoSFColor.h \
    lib/database/include/Inventor/fields/SoSFEngine.h \
    lib/database/include/Inventor/fields/SoSFEnum.h \
    lib/database/include/Inventor/fields/SoSFFloat.h \
    lib/database/include/Inventor/fields/SoSFImage.h \
    lib/database/include/Inventor/fields/SoSFLong.h \
    lib/database/include/Inventor/fields/SoSFMatrix.h \
    lib/database/include/Inventor/fields/SoSFName.h \
    lib/database/include/Inventor/fields/SoSFNode.h \
    lib/database/include/Inventor/fields/SoSFPath.h \
    lib/database/include/Inventor/fields/SoSFPlane.h \
    lib/database/include/Inventor/fields/SoSFRotation.h \
    lib/database/include/Inventor/fields/SoSFShort.h \
    lib/database/include/Inventor/fields/SoSFString.h \
    lib/database/include/Inventor/fields/SoSFTime.h \
    lib/database/include/Inventor/fields/SoSFTrigger.h \
    lib/database/include/Inventor/fields/SoSFUInt32.h \
    lib/database/include/Inventor/fields/SoSFULong.h \
    lib/database/include/Inventor/fields/SoSFUShort.h \
    lib/database/include/Inventor/fields/SoSFVec2f.h \
    lib/database/include/Inventor/fields/SoSFVec3f.h \
    lib/database/include/Inventor/fields/SoSFVec4f.h \
    lib/database/include/Inventor/fields/SoSubField.h
  QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS12

  FRAMEWORK_HEADERS13.path = Headers/manips
  FRAMEWORK_HEADERS13.files = \
    lib/interaction/include/Inventor/manips/SoCenterballManip.h \
    lib/interaction/include/Inventor/manips/SoDirectionalLightManip.h \
    lib/interaction/include/Inventor/manips/SoHandleBoxManip.h \
    lib/interaction/include/Inventor/manips/SoJackManip.h \
    lib/interaction/include/Inventor/manips/SoPointLightManip.h \
    lib/interaction/include/Inventor/manips/SoSpotLightManip.h \
    lib/interaction/include/Inventor/manips/SoTabBoxManip.h \
    lib/interaction/include/Inventor/manips/SoTrackballManip.h \
    lib/interaction/include/Inventor/manips/SoTransformBoxManip.h \
    lib/interaction/include/Inventor/manips/SoTransformerManip.h \
    lib/interaction/include/Inventor/manips/SoTransformManip.h
  QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS13

  FRAMEWORK_HEADERS14.path = Headers/misc
  FRAMEWORK_HEADERS14.files = \
    lib/database/include/Inventor/misc/SoAuditorList.h \
    lib/database/include/Inventor/misc/SoBase.h \
    lib/database/include/Inventor/misc/SoBasic.h \
    lib/database/include/Inventor/misc/SoByteStream.h \
    lib/database/include/Inventor/misc/SoCallbackList.h \
    lib/database/include/Inventor/misc/SoChildList.h \
    lib/database/include/Inventor/misc/SoCompactPathList.h \
    lib/database/include/Inventor/misc/SoNormalGenerator.h \
    lib/database/include/Inventor/misc/SoNotification.h \
    lib/database/include/Inventor/misc/SoState.h \
    lib/database/include/Inventor/misc/SoTempPath.h \
    lib/database/include/Inventor/misc/SoTranscribe.h
  QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS14

  FRAMEWORK_HEADERS15.path = Headers/misc/upgraders
  FRAMEWORK_HEADERS15.files = \
    lib/database/include/Inventor/misc/upgraders/SoV1QuadMeshKit.h \
    lib/database/include/Inventor/misc/upgraders/SoUpgrader.h \
    lib/database/include/Inventor/misc/upgraders/SoV1AppearanceKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1BaseKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1CameraKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1ConeKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1CubeKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1CustomNode.h \
    lib/database/include/Inventor/misc/upgraders/SoV1CylinderKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1DirectionalLightKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1FaceSetKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1GroupKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1IndexedFaceSetKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1IndexedLineSetKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1IndexedNurbsCurveKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1IndexedNurbsSurfaceKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1IndexedTriangleMeshKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1LightKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1LineSetKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1NodekitCatalog.h \
    lib/database/include/Inventor/misc/upgraders/SoV1NodekitParts.h \
    lib/database/include/Inventor/misc/upgraders/SoV1NurbsCurveKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1NurbsSurfaceKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1OrthographicCameraKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1PerspectiveCameraKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1PointLightKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1PointSetKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1SceneKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1ShapeKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1SphereKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1SpotLightKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1SubKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1Text2Kit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1Text3Kit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1TriangleStripSetKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1VertexShapeKit.h \
    lib/database/include/Inventor/misc/upgraders/SoV1WrapperKit.h
    lib/nodekits/include/Inventor/misc/upgraders/SoV1NodeKit.h \
  QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS15

  FRAMEWORK_HEADERS16.path = Headers/nodekits
  FRAMEWORK_HEADERS16.files = \
    lib/interaction/include/Inventor/nodekits/SoInteractionKit.h \
    lib/nodekits/include/Inventor/nodekits/SoAppearanceKit.h \
    lib/nodekits/include/Inventor/nodekits/SoBaseKit.h \
    lib/nodekits/include/Inventor/nodekits/SoCameraKit.h \
    lib/nodekits/include/Inventor/nodekits/SoLightKit.h \
    lib/nodekits/include/Inventor/nodekits/SoNodeKit.h \
    lib/nodekits/include/Inventor/nodekits/SoNodekitCatalog.h \
    lib/nodekits/include/Inventor/nodekits/SoNodeKitListPart.h \
    lib/nodekits/include/Inventor/nodekits/SoNodekitParts.h \
    lib/nodekits/include/Inventor/nodekits/SoSceneKit.h \
    lib/nodekits/include/Inventor/nodekits/SoSeparatorKit.h \
    lib/nodekits/include/Inventor/nodekits/SoShapeKit.h \
    lib/nodekits/include/Inventor/nodekits/SoSubKit.h \
    lib/nodekits/include/Inventor/nodekits/SoWrapperKit.h
  QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS16

  FRAMEWORK_HEADERS17.path = Headers/nodes
  FRAMEWORK_HEADERS17.files = \
    lib/mevis/include/Inventor/nodes/SoPolygonOffset.h \
    lib/database/include/Inventor/nodes/SoAnnotation.h \
    lib/database/include/Inventor/nodes/SoArray.h \
    lib/database/include/Inventor/nodes/SoAsciiText.h \
    lib/database/include/Inventor/nodes/SoBaseColor.h \
    lib/database/include/Inventor/nodes/SoBlinker.h \
    lib/database/include/Inventor/nodes/SoCallback.h \
    lib/database/include/Inventor/nodes/SoCamera.h \
    lib/database/include/Inventor/nodes/SoClipPlane.h \
    lib/database/include/Inventor/nodes/SoColorIndex.h \
    lib/database/include/Inventor/nodes/SoComplexity.h \
    lib/database/include/Inventor/nodes/SoCone.h \
    lib/database/include/Inventor/nodes/SoCoordinate3.h \
    lib/database/include/Inventor/nodes/SoCoordinate4.h \
    lib/database/include/Inventor/nodes/SoCube.h \
    lib/database/include/Inventor/nodes/SoCylinder.h \
    lib/database/include/Inventor/nodes/SoDirectionalLight.h \
    lib/database/include/Inventor/nodes/SoDrawStyle.h \
    lib/database/include/Inventor/nodes/SoEnvironment.h \
    lib/database/include/Inventor/nodes/SoEventCallback.h \
    lib/database/include/Inventor/nodes/SoFaceSet.h \
    lib/database/include/Inventor/nodes/SoFile.h \
    lib/database/include/Inventor/nodes/SoFont.h \
    lib/database/include/Inventor/nodes/SoFontStyle.h \
    lib/database/include/Inventor/nodes/SoGroup.h \
    lib/database/include/Inventor/nodes/SoIndexedFaceSet.h \
    lib/database/include/Inventor/nodes/SoIndexedLineSet.h \
    lib/database/include/Inventor/nodes/SoIndexedNurbsCurve.h \
    lib/database/include/Inventor/nodes/SoIndexedNurbsSurface.h \
    lib/database/include/Inventor/nodes/SoIndexedShape.h \
    lib/database/include/Inventor/nodes/SoIndexedTriangleStripSet.h \
    lib/database/include/Inventor/nodes/SoInfo.h \
    lib/database/include/Inventor/nodes/SoLOD.h \
    lib/database/include/Inventor/nodes/SoLabel.h \
    lib/database/include/Inventor/nodes/SoLevelOfDetail.h \
    lib/database/include/Inventor/nodes/SoLight.h \
    lib/database/include/Inventor/nodes/SoLightModel.h \
    lib/database/include/Inventor/nodes/SoLineSet.h \
    lib/database/include/Inventor/nodes/SoLinearProfile.h \
    lib/database/include/Inventor/nodes/SoLocateHighlight.h \
    lib/database/include/Inventor/nodes/SoMaterial.h \
    lib/database/include/Inventor/nodes/SoMaterialBinding.h \
    lib/database/include/Inventor/nodes/SoMatrixTransform.h \
    lib/database/include/Inventor/nodes/SoMultipleCopy.h \
    lib/database/include/Inventor/nodes/SoNode.h \
    lib/database/include/Inventor/nodes/SoNodes.h \
    lib/database/include/Inventor/nodes/SoNonIndexedShape.h \
    lib/database/include/Inventor/nodes/SoNormal.h \
    lib/database/include/Inventor/nodes/SoNormalBinding.h \
    lib/database/include/Inventor/nodes/SoNurbsCurve.h \
    lib/database/include/Inventor/nodes/SoNurbsProfile.h \
    lib/database/include/Inventor/nodes/SoNurbsSurface.h \
    lib/database/include/Inventor/nodes/SoOrthographicCamera.h \
    lib/database/include/Inventor/nodes/SoPackedColor.h \
    lib/database/include/Inventor/nodes/SoPathSwitch.h \
    lib/database/include/Inventor/nodes/SoPendulum.h \
    lib/database/include/Inventor/nodes/SoPerspectiveCamera.h \
    lib/database/include/Inventor/nodes/SoPickStyle.h \
    lib/database/include/Inventor/nodes/SoPointLight.h \
    lib/database/include/Inventor/nodes/SoPointSet.h \
    lib/database/include/Inventor/nodes/SoProfile.h \
    lib/database/include/Inventor/nodes/SoProfileCoordinate2.h \
    lib/database/include/Inventor/nodes/SoProfileCoordinate3.h \
    lib/database/include/Inventor/nodes/SoQuadMesh.h \
    lib/database/include/Inventor/nodes/SoResetTransform.h \
    lib/database/include/Inventor/nodes/SoRotation.h \
    lib/database/include/Inventor/nodes/SoRotationXYZ.h \
    lib/database/include/Inventor/nodes/SoRotor.h \
    lib/database/include/Inventor/nodes/SoScale.h \
    lib/database/include/Inventor/nodes/SoSeparator.h \
    lib/database/include/Inventor/nodes/SoShape.h \
    lib/database/include/Inventor/nodes/SoShapeHints.h \
    lib/database/include/Inventor/nodes/SoShuttle.h \
    lib/database/include/Inventor/nodes/SoSphere.h \
    lib/database/include/Inventor/nodes/SoSpotLight.h \
    lib/database/include/Inventor/nodes/SoSubNode.h \
    lib/database/include/Inventor/nodes/SoSwitch.h \
    lib/database/include/Inventor/nodes/SoText2.h \
    lib/database/include/Inventor/nodes/SoText3.h \
    lib/database/include/Inventor/nodes/SoTexture2.h \
    lib/database/include/Inventor/nodes/SoTexture2Transform.h \
    lib/database/include/Inventor/nodes/SoTextureCoordinate2.h \
    lib/database/include/Inventor/nodes/SoTextureCoordinateBinding.h \
    lib/database/include/Inventor/nodes/SoTextureCoordinateDefault.h \
    lib/database/include/Inventor/nodes/SoTextureCoordinateEnvironment.h \
    lib/database/include/Inventor/nodes/SoTextureCoordinateFunction.h \
    lib/database/include/Inventor/nodes/SoTextureCoordinatePlane.h \
    lib/database/include/Inventor/nodes/SoTransform.h \
    lib/database/include/Inventor/nodes/SoTransformSeparator.h \
    lib/database/include/Inventor/nodes/SoTransformation.h \
    lib/database/include/Inventor/nodes/SoTranslation.h \
    lib/database/include/Inventor/nodes/SoTriangleStripSet.h \
    lib/database/include/Inventor/nodes/SoUnits.h \
    lib/database/include/Inventor/nodes/SoVertexProperty.h \
    lib/database/include/Inventor/nodes/SoVertexShape.h \
    lib/database/include/Inventor/nodes/SoWWWAnchor.h \
    lib/database/include/Inventor/nodes/SoWWWInline.h \
    lib/interaction/include/Inventor/nodes/SoAntiSquish.h \
    lib/interaction/include/Inventor/nodes/SoSelection.h \
    lib/interaction/include/Inventor/nodes/SoSurroundScale.h
  QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS17

  FRAMEWORK_HEADERS18.path = Headers/projectors
  FRAMEWORK_HEADERS18.files = \
    lib/database/include/Inventor/projectors/SbCylinderPlaneProjector.h \
    lib/database/include/Inventor/projectors/SbCylinderProjector.h \
    lib/database/include/Inventor/projectors/SbCylinderSectionProjector.h \
    lib/database/include/Inventor/projectors/SbCylinderSheetProjector.h \
    lib/database/include/Inventor/projectors/SbLineProjector.h \
    lib/database/include/Inventor/projectors/SbPlaneProjector.h \
    lib/database/include/Inventor/projectors/SbProjector.h \
    lib/database/include/Inventor/projectors/SbProjectors.h \
    lib/database/include/Inventor/projectors/SbSpherePlaneProjector.h \
    lib/database/include/Inventor/projectors/SbSphereProjector.h \
    lib/database/include/Inventor/projectors/SbSphereSectionProjector.h \
    lib/database/include/Inventor/projectors/SbSphereSheetProjector.h
  QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS18

  FRAMEWORK_HEADERS19.path = Headers/sensors
  FRAMEWORK_HEADERS19.files = \
    lib/database/include/Inventor/sensors/SoAlarmSensor.h \
    lib/database/include/Inventor/sensors/SoDataSensor.h \
    lib/database/include/Inventor/sensors/SoDelayQueueSensor.h \
    lib/database/include/Inventor/sensors/SoFieldSensor.h \
    lib/database/include/Inventor/sensors/SoIdleSensor.h \
    lib/database/include/Inventor/sensors/SoNodeSensor.h \
    lib/database/include/Inventor/sensors/SoOneShotSensor.h \
    lib/database/include/Inventor/sensors/SoPathSensor.h \
    lib/database/include/Inventor/sensors/SoSensor.h \
    lib/database/include/Inventor/sensors/SoSensorManager.h \
    lib/database/include/Inventor/sensors/SoSensors.h \
    lib/database/include/Inventor/sensors/SoTimerQueueSensor.h \
    lib/database/include/Inventor/sensors/SoTimerSensor.h
  QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS19

  FRAMEWORK_HEADERS20.path = Headers/system
  FRAMEWORK_HEADERS20.files = \
    lib/mevis/include/Inventor/system/SbConfig.h \
    lib/mevis/include/Inventor/system/SbSystem.h
  QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS20
  
  build_oiv_installer {
    QMAKE_LFLAGS_SONAME = -Wl,-install_name,/Library/Frameworks/
  }
}
