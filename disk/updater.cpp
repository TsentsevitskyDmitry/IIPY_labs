#include "updater.h"
#include <iostream>

void Updater::process() {
    while(run) {
        emit update();
        Sleep(1000);
    }

    emit end_process();
}

void Updater::finished() {
    run = false;
}

void Updater::sendSignal() {
    emit update();
}

Updater::Updater() : run(true) {}
