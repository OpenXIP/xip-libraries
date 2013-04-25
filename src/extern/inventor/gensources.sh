#! /bin/sh

BUILDTOOLS=tools/ppp

$BUILDTOOLS/ppp < lib/database/src/so/nodes/SoCone.pp                        	> lib/database/src/so/nodes/SoCone.c++
$BUILDTOOLS/ppp < lib/database/src/so/nodes/SoCube.pp				> lib/database/src/so/nodes/SoCube.c++
$BUILDTOOLS/ppp < lib/database/src/so/nodes/SoCylinder.pp			> lib/database/src/so/nodes/SoCylinder.c++
$BUILDTOOLS/ppp < lib/database/src/so/nodes/SoFaceSet.pp			> lib/database/src/so/nodes/SoFaceSet.c++
$BUILDTOOLS/ppp < lib/database/src/so/nodes/SoIndexedFaceSet.pp			> lib/database/src/so/nodes/SoIndexedFaceSet.c++
$BUILDTOOLS/ppp < lib/database/src/so/nodes/SoIndexedLineSet.pp			> lib/database/src/so/nodes/SoIndexedLineSet.c++
$BUILDTOOLS/ppp < lib/database/src/so/nodes/SoIndexedTriangleStripSet.pp	> lib/database/src/so/nodes/SoIndexedTriangleStripSet.c++
$BUILDTOOLS/ppp < lib/database/src/so/nodes/SoLineSet.pp			> lib/database/src/so/nodes/SoLineSet.c++
$BUILDTOOLS/ppp < lib/database/src/so/nodes/SoPointSet.pp			> lib/database/src/so/nodes/SoPointSet.c++
$BUILDTOOLS/ppp < lib/database/src/so/nodes/SoQuadMesh.pp			> lib/database/src/so/nodes/SoQuadMesh.c++
$BUILDTOOLS/ppp < lib/database/src/so/nodes/SoSphere.pp				> lib/database/src/so/nodes/SoSphere.c++
$BUILDTOOLS/ppp < lib/database/src/so/nodes/SoTriangleStripSet.pp		> lib/database/src/so/nodes/SoTriangleStripSet.c++
