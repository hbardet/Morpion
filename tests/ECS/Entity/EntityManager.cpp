#include <doctest/doctest.h>
#include "ECS/Entity/EntityManager/EntityManager.hh"

TEST_CASE("Entity Manager") {
    ECS::EntityManager::EntityManager manager;
    Signature sig;
    std::size_t entityId;
    Signature pseudoSig = Signature().set();
    std::vector<std::size_t> entities;

    //Check original state
    entities = manager.getEntities();
    CHECK(entities.empty());

    //create Entity
    entityId = manager.createEntity();
    sig = manager.getSignature(entityId);
    CHECK(sig.none() == true);

    //set Entity Signature
    manager.setSignature(entityId, pseudoSig);
    sig = manager.getSignature(entityId);
    CHECK(sig == pseudoSig);

    entities = manager.getEntities();
    CHECK_FALSE(entities.empty());

    //destroy Entity

    manager.destroyEntity(entityId);
    sig = manager.getSignature(entityId);
    CHECK(sig != pseudoSig);
    CHECK(sig.none() == true);
    entities = manager.getEntities();
    CHECK(entities.empty());
}
