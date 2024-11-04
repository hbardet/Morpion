#include "TextfieldInput.hh"

void ECS::Systems::TextFieldInputSystem::update(
    ECS::ComponentManager::SparseArray<ECS::Components::TextField> &textFields,
    const std::vector<std::size_t> &entities) {

    Vector2 mousePosition = GetMousePosition();
    bool mouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    for (auto entity : entities) {
        if (textFields[entity].has_value()) {
            auto &textField = textFields[entity].value();

            if (mouseClicked && textField.isMouseOver(mousePosition.x, mousePosition.y)) {
                textField.setActive(true);
            } else if (mouseClicked) {
                textField.setActive(false);
            }

            if (textField.isActive()) {
                handleKeyboardInput(textField);
            }
        }
    }
}

void ECS::Systems::TextFieldInputSystem::handleKeyboardInput(ECS::Components::TextField &textField) {
    int key = GetCharPressed();

    while (key > 0) {
        if ((key >= 32) && (key <= 125)) {
            textField.setText(textField.getText() + static_cast<char>(key));
        }
            key = GetCharPressed();
        }

    if (IsKeyPressed(KEY_BACKSPACE) && !textField.getText().empty()) {
        std::string currentText = textField.getText();
        currentText.pop_back();
        textField.setText(currentText);
    }
}
