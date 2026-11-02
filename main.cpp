#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <string>
#include <queue>

// --- 1. Object Pooling System ---
template <typename T>
class ObjectPool {
private:
    std::vector<std::unique_ptr<T>> pool;
    std::queue<T*> availableObjects;
    size_t capacity;

public:
    explicit ObjectPool(size_t initialCapacity) : capacity(initialCapacity) {
        pool.reserve(capacity);
        for (size_t i = 0; i < capacity; ++i) {
            auto obj = std::make_unique<T>();
            availableObjects.push(obj.get());
            pool.push_back(std::move(obj));
        }
        std::cout << "[ObjectPool] Initialized with capacity: " << capacity << "\n";
    }

    T* acquire() {
        if (availableObjects.empty()) {
            std::cout << "[ObjectPool] Warning: Pool exhausted! Expanding capacity...\n";
            auto obj = std::make_unique<T>();
            T* ptr = obj.get();
            pool.push_back(std::move(obj));
            return ptr;
        }
        T* ptr = availableObjects.front();
        availableObjects.pop();
        return ptr;
    }

    void release(T* ptr) {
        availableObjects.push(ptr);
    }

    size_t getAvailableCount() const { return availableObjects.size(); }
};

// Mock Entity for testing the Object Pool
struct Projectile {
    float x = 0.0f, y = 0.0f;
    bool active = false;
    void reset() { x = 0.0f; y = 0.0f; active = true; }
};

// --- 2. Procedural Node-Graph Level Generator ---
enum class RoomType { Entrance, Corridor, Chamber, BossArena, TreasureVault };

struct RoomNode {
    int id;
    RoomType type;
    int x, y;
    std::vector<int> connectedRooms;
    std::vector<std::string> obstacles;
    std::vector<std::string> spawnPoints;
};

class LevelGenerator {
public:
    std::vector<RoomNode> generateLevel(int targetRooms) {
        std::cout << "[LevelGenerator] Constructing node-graph dungeon (" << targetRooms << " rooms)...\n";
        std::vector<RoomNode> dungeonGraph;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> coordDist(0, 50);

        for (int i = 0; i < targetRooms; ++i) {
            RoomNode room;
            room.id = i;
            room.x = coordDist(gen);
            room.y = coordDist(gen);

            if (i == 0) {
                room.type = RoomType::Entrance;
                room.spawnPoints.push_back("Player_Spawn");
            } else if (i == targetRooms - 1) {
                room.type = RoomType::BossArena;
                room.spawnPoints.push_back("Boss_Spawn");
            } else {
                room.type = (i % 3 == 0) ? RoomType::TreasureVault : RoomType::Chamber;
                room.obstacles.push_back("Collapsed_Pillar");
                room.spawnPoints.push_back("Skeleton_Minion");
            }

            if (i > 0) {
                room.connectedRooms.push_back(i - 1);
                dungeonGraph[i - 1].connectedRooms.push_back(i);
            }

            dungeonGraph.push_back(room);
        }
        std::cout << "[LevelGenerator] Dungeon graph successfully compiled with " << dungeonGraph.size() << " nodes.\n";
        return dungeonGraph;
    }
};

// --- 3. Game State Manager ---
enum class GameState { MainMenu, Gameplay, Paused, GameOver };

class GameStateManager {
public:
    void changeState(GameState state) {
        std::cout << "[Engine] Game State transitioned to Gameplay.\n";
    }
};

// --- 4. Main Engine Entry Point ---
int main() {
    std::cout << "=== Initializing Dark Fantasy Game Engine (Full Stack) ===\n";
    
    // Initialize State Manager
    GameStateManager stateMgr;
    stateMgr.changeState(GameState::Gameplay);

    // Generate Dungeon Graph
    LevelGenerator levelGen;
    auto dungeon = levelGen.generateLevel(8);

    // Initialize Object Pool for Projectiles (Pre-allocate 10 objects)
    ObjectPool<Projectile> projectilePool(10);

    // Simulate acquiring and releasing pooled projectiles during combat
    std::cout << "[Engine] Simulating combat projectile pooling...\n";
    Projectile* p1 = projectilePool.acquire();
    p1->reset();
    std::cout << "  - Acquired Projectile 1. Available in pool: " << projectilePool.getAvailableCount() << "\n";

    Projectile* p2 = projectilePool.acquire();
    p2->reset();
    std::cout << "  - Acquired Projectile 2. Available in pool: " << projectilePool.getAvailableCount() << "\n";

    projectilePool.release(p1);
    std::cout << "  - Released Projectile 1 back to pool. Available: " << projectilePool.getAvailableCount() << "\n";

    std::cout << "=== Engine Running at 60 FPS Target (Object Pooling Integrated) ===\n";
    return 0;
}
