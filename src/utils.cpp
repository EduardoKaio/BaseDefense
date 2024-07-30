#include "utils.h"
#include <cmath>

sf::Vector2f normalize(const sf::Vector2f& vector) {
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (length != 0) {
        return vector / length;
    }
    return vector;
}