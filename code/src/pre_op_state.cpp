#include <context.hpp>
#include <init_state.hpp>
#include <op_state.hpp>
#include <pre_op_state.hpp>
#include "pi_controller.hpp"
#include "constants.hpp"

void Pre_op_state::on_do() {
    if (Serial.available() > 0) {
        char command = Serial.read();
        switch (command) {
        case 'p': // Set P-controller
            delete this->context_->control; // Clean up existing controller
            this->context_->control = new P_controller(KP, MAX_VELOCITY, CONTROLLER_UPDATE_RATE_MS);
            Serial.println("P-controller selected.");
            break;
        case 'i': // Set PI-controller
            delete this->context_->control; // Clean up existing controller
            this->context_->control = new PI_Controller(KP, KI, MAX_VELOCITY, CONTROLLER_UPDATE_RATE_MS);
            Serial.println("PI-controller selected.");
            break;
        case 'k': // Set KP value
            Serial.println("Enter new KP value:");
            while (Serial.available() == 0) {} // Wait for input
            KP = Serial.parseFloat();
            Serial.print("KP set to: ");
            Serial.println(KP);
            break;
        case 't': // Set TI value
            Serial.println("Enter new TI value:");
            while (Serial.available() == 0) {} // Wait for input
            TI = Serial.parseFloat();
            Serial.print("TI set to: ");
            Serial.println(TI);
            break;
        default:
            Serial.println("Invalid command. Please try again.");
            break;
        }
    }
}

void Pre_op_state::on_entry() {
  Serial.println("Please enter a command:");
  Serial.println("'p' - Set P-controller");
  Serial.println("'i' - Set PI-controller");
  Serial.println("'k' - Set KP value");
  Serial.println("'t' - Set TI value");
  this->context_->led->set_bandwidth(LED_1HZ_BAND);
  this->context_->led->set_mode(BLINK);
};

void Pre_op_state::on_exit() {};

void Pre_op_state::on_reset() {
  this->context_->transition_to(new Init_state);
};

void Pre_op_state::on_set_pre_op() {};

void Pre_op_state::on_set_op() { this->context_->transition_to(new Op_state); };

String Pre_op_state::get_name() { return this->name; };
