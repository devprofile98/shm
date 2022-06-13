#include "birdModel.hpp"

BirdActor::BirdActor(){
    SHM::Engine::getRenderer()->m_actors.push_back(this);
    std::cout << "BIRD Actor created!" << std::endl;
}
BirdActor::~BirdActor(){
    std::cout << "BIRD Actor destroyed!" << std::endl;
}

void BirdActor::setUpModel() {
    this->model->setPosition({-3.0f, 5.7f , 0.0f});
    this->model->setScale({0.5f, 0.5f, 0.5f});
    // this->model->setRotation({0.0f, 1.0f, 0.0f});
    this->model->setRotation({0.0f , -1.0f, 0.0f});
}
void BirdActor::eachFrame() {}