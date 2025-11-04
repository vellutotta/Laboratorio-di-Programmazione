
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<thread>
#include <vector>
#include <chrono>
#include "timer.h"

using namespace std;
using namespace sf;



int main() {

    RenderWindow window(VideoMode(800, 600), "Progress Bar");

    SFMLProgressBar progressBar(200, 300, 400, 30);

    Timer timer(5.0f); // 5 secondi di durata
    timer.addObserver(&progressBar);


    timer.start();

    while (window.isOpen()) {
        Event event;


        while (window.pollEvent(event)) {                     //mi restituisce true se c'è un evento disponibile
            if (event.type == Event::Closed) {
                window.close();
                timer.stop();
            }
        }

        window.clear(Color(0,0,0));
        progressBar.draw(window);
        window.display();
    }

    return 0;
}













    


