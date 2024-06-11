#include <random>
#include <chrono>
#include <iostream>
#include <fstream>
#include "../header/Chapter2.h"
#include "../header/GameExceptions.h"
#include "../header/Vampir.h"
#include "../header/Skelet.h"
#include "../header/Zombie.h"

std::unordered_map<unsigned long long, bool> Chapter2::frq = {};
std::vector<Position> Chapter2::poziti = {
        {100, 100}, {150, 250}, {350, 250}, {700, 200}, {1000, 300},
        {1000, 1100}, {900, 100}, {1050, 250}, {1250, 1250}, {790, 900},
        {1100, 100}, {100, 1100}, {50, 1050}, {200, 800}, {300, 700},
        {450, 50}, {500, 1000}, {950, 950}, {1100, 1100}, {850, 850},
        {75, 600}, {675, 25}, {725, 75}, {775, 125}, {825, 175},
        {875, 225}, {925, 275}, {975, 325}, {1025, 375}, {1075, 425}
};

Chapter2::Chapter2() : wave(BEGIN), stage(Playing) {
    try {
        readFromFile("maps/map2.txt");
        generateEnemies();
    } catch (const FileLoadException& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }
}

void Chapter2::generateEnemies() {
    switch (wave) {
        case BEGIN:
            populate(BEGIN, 4);
            break;
        case MEDIUM:
            populate(MEDIUM, 5);
            break;
        case HARD:
            populate(BEGIN, 3);
            populate(MEDIUM, 4);
            populate(HARD, 2);
            break;
        default:
            populate(BEGIN, 4);
    }
    frq.clear();
}

[[maybe_unused]]Chapter2::Chapter2(const Chapter2& other)
        : wave(other.wave), stage(other.stage), enemies(other.enemies),
          main_player(other.main_player), help_player(other.help_player), map2(other.map2) {
}

Chapter2& Chapter2::operator=(Chapter2 other) {
    swap(*this, other);
    return *this;
}

void swap(Chapter2& first, Chapter2& second) noexcept {
    using std::swap;
    swap(first.wave, second.wave);
    swap(first.stage, second.stage);
    swap(first.enemies, second.enemies);
    swap(first.main_player, second.main_player);
    swap(first.help_player, second.help_player);
    swap(first.map2, second.map2);
}

void Chapter2::update() {
    main_player.handleInput();
    main_player.update(Map::convert_map(map2));

    for (auto& it : enemies) {
        if (it->getEnemyHp() > 0) {
            it->update(main_player, help_player);
        }
    }

    if (allEnemiesDefeated()) {
        switch (wave) {
            case BEGIN:
                main_player.buff(120, 6);
                help_player.heal(150);
                wave = MEDIUM;
                break;
            case MEDIUM:
                main_player.buff(140, 9);
                help_player.heal(170);
                wave = HARD;
                break;
            case HARD:
                stage = Victory;
                break;
            default:
                main_player.buff(100, 5);
                help_player.heal(100);
                wave = BEGIN;
        }

        enemies.clear();
        generateEnemies();
        std::cout << main_player.getHp() << " " << main_player.get_attack() << '\n';
        std::cout << help_player.getHp() << "\n";

    }

    if (main_player.getHp() < 0 || help_player.getHp() < 0) {
        stage = Defeat;
    }
}

bool Chapter2::allEnemiesDefeated() {
    for (const auto& enemy : enemies) {
        if (enemy->getEnemyHp() > 0) {
            return false;
        }
    }
    return true;
}

void Chapter2::render(sf::RenderWindow &window) {
    Map::draw(Map::convert_map(map2), window);
    help_player.drawNPC(window);
    for (auto& it : enemies) {
        if (it->getEnemyHp() > 0) {
            it->drawEnemy(window);
        }
    }
    main_player.drawPlayer(window);
}

int Chapter2::keepPlaying() {
    switch (stage) {
        case Victory: return 1;
        case Defeat: return 0;
        default: return 2;
    }
}

void Chapter2::readFromFile(const std::string &filePath) {
    std::ifstream fin(filePath);
    if (!fin.is_open()) {
        throw FileLoadException("Could not open file: " + filePath);
    }

    int index = 0;
    std::string line;
    while (std::getline(fin, line) && index < Map_height) {
        map2[index] = line;
        index++;
    }

    if (index < Map_height) {
        throw FileLoadException("File is incomplete: " + filePath);
    }

    fin.close();
}

void Chapter2::populate(WaveLevel level, int count) {
    for (int i = 0; i < count; ++i) {
        auto enemy = createEnemy(level);
        Position pos = getRandomPosition();
        enemy->positionUpdate(pos.x, pos.y);
        enemies.emplace_back(std::move(enemy));
    }
}

Position Chapter2::getRandomPosition() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned long long> distrib(0, poziti.size() - 1);

    unsigned long long number = distrib(gen);
    while (frq[number]) {
        number = distrib(gen);
    }
    frq[number] = true;
    return poziti[number];
}

std::shared_ptr<Enemy> Chapter2::createEnemy(WaveLevel level) {
    switch (level) {
        case BEGIN: return std::make_shared<Vampir>();
        case MEDIUM: return std::make_shared<Skelet>();
        case HARD: return std::make_shared<Zombie>();
        default : std::cout << "Nu exista acest timp de enemy" << '\n', exit(0);
    }
}

void Chapter2::testCopyAndSwap() {
    Skelet original_skelet(100, 10, 1.5, "textures/skelet.png");
    Vampir original_vampir(100, 15, 2.0, "textures/vampir.png");

    const Skelet& copied_skelet(original_skelet);
    const Vampir& copied_vampir(original_vampir);

    std::cout << "Original Skelet HP: " << original_skelet.getEnemyHp() << std::endl;
    std::cout << "Copied Skelet HP: " << copied_skelet.getEnemyHp() << std::endl;
    std::cout << "Original Vampir HP: " << original_vampir.getEnemyHp() << std::endl;
    std::cout << "Copied Vampir HP: " << copied_vampir.getEnemyHp() << std::endl;

    Skelet assigned_skelet;
    assigned_skelet = original_skelet;

    Vampir assigned_vampir;
    assigned_vampir = original_vampir;

    std::cout << "Assigned Skelet HP: " << assigned_skelet.getEnemyHp() << std::endl;
    std::cout << "Assigned Vampir HP: " << assigned_vampir.getEnemyHp() << std::endl;
}
