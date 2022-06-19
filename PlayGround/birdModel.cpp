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
    SHM::Engine::getCamera()->attachTo(this, (uint8_t)SHM::Camera::ATTACH::X);
    this->m_physic_component = new BirdPhysic{this->model->getPosition(), {0.1f, 0.0f }, true};
}
void BirdActor::eachFrame() {
    if (this->m_physic_component->isAwake)
        this->model->setPosition({this->model->getPosition()->x + 0.05, 5.7, 0});
}