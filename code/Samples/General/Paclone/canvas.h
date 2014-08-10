#pragma once
//------------------------------------------------------------------------------
/**
    XY-Canvas for sprite tiles.
*/
#include "Core/Assert.h"
#include "Render/Setup/MeshSetup.h"
#include "sprites.h"

namespace Paclone {
    
class canvas {
public:
    // constructor
    canvas();
    
    /// setup the canvas
    void Setup(int numTilesX, int numTilesY, int tileWidth, int tileHeight, int numSprites);
    /// discard the cancas
    void Discard();
    /// return true if canvas has been setup
    bool IsValid() const;
    /// render the canvas
    void Render();
    
    /// copy a character map (use Sheet::CharMap to convert chars to sprite ids)
    void CopyCharMap(int tileX, int tileY, int tileW, int tileH, const char* charMap);
    /// clamp x-coordinate to valid area
    int ClampX(int tileX) const;
    /// clamp y-coordinate to valid area
    int ClampY(int tileY) const;
    /// set a dynamic sprite
    void SetSprite(int index, Sheet::SpriteId sprite, int pixX, int pixY, int pixW, int pixH);
    /// set a static tile
    void SetTile(Sheet::SpriteId sprite, int tileX, int tileY);

private:
    /// write a vertex
    int writeVertex(int index, float x, float y, float u, float v);
    /// update vertices, returns pointer to and size of vertex data
    const void* updateVertices(Oryol::int32& outNumBytes);
    
    bool isValid;
    int numTilesX;
    int numTilesY;
    int tileWidth;
    int tileHeight;
    int canvasWidth;
    int canvasHeight;
    int numSprites;
    int numVertices;
    Oryol::Resource::Id mesh;
    Oryol::Resource::Id prog;
    Oryol::Resource::Id drawState;
    Oryol::Resource::Id texture;

    static const int MaxWidth = 64;
    static const int MaxHeight = 64;
    Sheet::SpriteId tiles[MaxWidth * MaxHeight];
    
    static const int MaxNumSprites = 8;
    struct sprite {
        Sheet::SpriteId id = Sheet::InvalidSprite;
        int x = 0;
        int y = 0;
        int w = 0;
        int h = 0;
    } sprites[MaxNumSprites];
    
    struct vertex {
        float x, y, u, v;
    };
    static const int MaxNumVertices = MaxWidth * MaxHeight * 6;
    vertex vertexBuffer[MaxNumVertices];
};

} // namespace Paclone

