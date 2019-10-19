class TreeModel
{
private:
    Mesh mesh_;
    Texture bark_;
    Texture leaves_;
};

class Tree
{
private:
    TreeModel* model_;

    Vector position_;
    double height_;
    double thickness_;
    Color barkTint_;
    Color leafTint_;
};

class Terrain
{
public:
    Terrian(int movementCost,
            bool isWater,
            Texture texture)
    : movementCost_(movementCost),
      isWater_(isWater),
      texture_(texture)
      {}

    int getMovementCost() const { return movementCost_; }
    bool isWater() const { return isWater_; }
    const Texture& getTexture() const { return texture_; }

private:
    int movementCost_;
    bool isWater_;
    Texture texture_;
};

class World
{
public:
    World()
    : grassTerrain_(1, false, GRASS_TEXTURE),
      hillTerrain_(3, false, HILL_TEXTURE),
      riverTerrain_(2, true, RIVER_TEXTURE)
    {}

private:
    Terrain* tiles_[WIDTH][HEIGHT];
    Terrian grassTerrain_;
    Terrian hillTerrain_;
    Terrian riverTerrain_;
};