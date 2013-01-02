//
// Copyright (c) 2008-2013 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include "GraphicsDefs.h"
#include "RefCounted.h"

namespace Urho3D
{

class XMLElement;
class XMLFile;

/// Rendering path command types.
enum RenderCommandType
{
    CMD_NONE = 0,
    CMD_CLEAR,
    CMD_SCENEPASS,
    CMD_QUAD,
    CMD_FORWARDLIGHTS,
    CMD_LIGHTVOLUMES,
    CMD_UNKNOWN
};

/// Rendering path sorting modes.
enum RenderCommandSortMode
{
    SORT_FRONTTOBACK = 0,
    SORT_BACKTOFRONT
};

/// Rendertarget size mode.
enum RenderTargetSizeMode
{
    SIZE_ABSOLUTE = 0,
    SIZE_RENDERTARGETDIVISOR,
    SIZE_VIEWPORTDIVISOR
};

/// Rendertarget definition.
struct RenderTargetInfo
{
    /// Construct.
    RenderTargetInfo() :
        size_(IntVector2::ZERO),
        sizeMode_(SIZE_ABSOLUTE),
        active_(true),
        filtered_(false)
    {
    }
    
    /// Read from an XML element.
    void LoadParameters(const XMLElement& element);
    
    /// Name.
    String name_;
    /// Tag name.
    String tag_;
    /// Texture format.
    unsigned format_;
    /// Size.
    IntVector2 size_;
    /// Size mode.
    RenderTargetSizeMode sizeMode_;
    /// Active flag.
    bool active_;
    /// Filtering flag.
    bool filtered_;
};

/// Rendering path command.
struct RenderPathCommand
{
    /// Construct.
    RenderPathCommand() :
        clearFlags_(0),
        active_(true),
        useFogColor_(false),
        markToStencil_(false),
        useScissor_(false),
        vertexLights_(false)
    {
    }
    
    /// Read from an XML element.
    void LoadParameters(const XMLElement& element);
    
    /// Tag name.
    String tag_;
    /// Command type.
    RenderCommandType type_;
    /// Sorting mode.
    RenderCommandSortMode sortMode_;
    /// Scene pass hash.
    StringHash pass_;
    /// Clear flags.
    unsigned clearFlags_;
    /// Clear color.
    Color clearColor_;
    /// Clear depth.
    float clearDepth_;
    /// Clear stencil value.
    unsigned clearStencil_;
    /// Active flag.
    bool active_;
    /// Use fog color for clearing.
    bool useFogColor_;
    /// Mark to stencil flag.
    bool markToStencil_;
    /// Vertex lights flag.
    bool vertexLights_;
    /// Scissor optimization flag.
    bool useScissor_;
    /// Vertex shader name.
    String vertexShaderName_;
    /// Pixel shader name.
    String pixelShaderName_;
    /// Textures.
    String textureNames_[MAX_TEXTURE_UNITS];
    /// %Shader parameters.
    HashMap<StringHash, Vector4> shaderParameters_;
    /// Output rendertarget names.
    Vector<String> outputs_;
};

/// Rendering path definition.
class RenderPath : public RefCounted
{
public:
    /// Construct.
    RenderPath();
    /// Destruct.
    ~RenderPath();
    
    /// Clone the rendering path.
    SharedPtr<RenderPath> Clone();
    /// Read from an XML file. Return true if successful.
    bool LoadParameters(XMLFile* file);
    /// Append data from an XML file. Return true if successful.
    bool Append(XMLFile* file);
    /// Activate/inactivate commands and rendertargets by tag.
    void SetActive(const String& tag, bool active);
    /// Toggle activation of commands and rendertargets by tag.
    void ToggleActive(const String& tag);
    
    /// Rendertargets.
    Vector<RenderTargetInfo> renderTargets_;
    /// Rendering commands.
    Vector<RenderPathCommand> commands_;
};

}