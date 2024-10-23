
mkdir -p include/entt
mkdir -p include/nlohmann

wget https://raw.githubusercontent.com/skypjack/entt/refs/heads/master/single_include/entt/entt.hpp \
  -O include/entt/entt.hpp
wget https://raw.githubusercontent.com/nlohmann/json/refs/heads/develop/single_include/nlohmann/json.hpp \
  -O include/nlohmann/json.hpp
