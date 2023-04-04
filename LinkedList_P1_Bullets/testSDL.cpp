#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


// Estructura para la nave
struct Ship {
  SDL_Texture* texture;
  SDL_Rect rect;
  // Otras propiedades de la nave
};

// Estructura para la bala
struct Bullet {
  SDL_Texture* texture;
  SDL_Rect rect;
  // Otras propiedades de la bala
};

// Función para detectar colisiones entre dos rectángulos
bool CheckCollision(SDL_Rect a, SDL_Rect b) {
  return (a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.y + a.h > b.y);
}

// Función para actualizar la posición de las balas y detectar colisiones
void UpdateBullets(std::vector<Bullet>& bullets, std::vector<Ship>& ships) {
  // Actualiza la posición de cada bala
  for (auto& bullet : bullets) {
    bullet.rect.y -= bullet.speed;
  }

  // Verifica si una bala colisiona con una nave
  for (auto& bullet : bullets) {
    for (auto& ship : ships) {
      if (CheckCollision(bullet.rect, ship.rect)) {
        // La bala ha golpeado la nave
        // Hacer algo aquí, como reducir la vida de la nave, etc.
      }
    }
  }

  // Elimina las balas que han salido de la pantalla
  bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet& bullet) {
    return bullet.rect.y < 0;
  }), bullets.end());
}

// Función para actualizar la posición de las naves y detectar colisiones
void UpdateShips(std::vector<Ship>& ships) {
  // Actualiza la posición de cada nave
  for (auto& ship : ships) {
    // Implementar la lógica de movimiento aquí
  }

  // Verifica si una nave colisiona con otra nave
  for (auto& ship1 : ships) {
    for (auto& ship2 : ships) {
      if (&ship1 != &ship2 && CheckCollision(ship1.rect, ship2.rect)) {
        // Las dos naves han chocado
        // Hacer algo aquí, como reducir la vida de las naves, etc.
      }
    }
  }
}

// Función para renderizar las balas y las naves
void Render(SDL_Renderer* renderer, std::vector<Bullet>& bullets, std::vector<Ship>& ships) {
  // Renderiza todas las balas
  for (auto& bullet : bullets) {
    SDL_RenderCopy(renderer, bullet.texture, NULL, &bullet.rect);
  }