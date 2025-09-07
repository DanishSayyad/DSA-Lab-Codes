#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

// Constants
const Color white = Color::White;
const Color black = Color::Black;
const Color grey = Color(50, 50, 50);
const Color darkgrey = Color(70, 70, 70);
const Color blue = Color(118, 245, 245);
const Color tint = Color(255, 205, 89);
const int w = 1000, h = 600;

struct node {
    Texture image;
    Sprite img;
    node *next, *prev;
    node(Texture &i, Sprite &s) {
        image = i;
        img = s;
        next = NULL;
        prev = NULL;

        // Scale image to fit main box for maintaining aspect ratio
        Vector2u imgsize = image.getSize();
        float mainBoxWidth = w - 10.f * 2 - 120; // Main box width
        float mainBoxHeight = h - 80 - 10.f; // Main box height
        
        float scaleX = mainBoxWidth / imgsize.x;
        float scaleY = mainBoxHeight / imgsize.y;
        float scale = min(scaleX, scaleY); 
        
        img.setScale(scale, scale);
        
        // Center the image in the main box
        Vector2f scaledSize = Vector2f(imgsize.x * scale, imgsize.y * scale);
        float imageX = (10.f + 60) + (mainBoxWidth - scaledSize.x) / 2.0f;
        float imageY = 10.f + (mainBoxHeight - scaledSize.y) / 2.0f;
        img.setPosition(imageX, imageY);

        img.setTexture(image);
    }
};

class CLL {
    private:
        node *head, *current;
        int count, now;
    public:
        CLL();
        ~CLL();
        void addNode(string);
        void deleteNode();
        Sprite getImage(RenderWindow&);
        void toNext();
        void toPrev();
        int getCount() {
            return count;
        }
        int getNow() {
            return now;
        }
};

// Quickhand to create rectangles
RectangleShape setBox(float, float, float, float, Color, Color, float);

// Quickhand to crete text render
Text setText(string, Font&, int, float, float, Color);

// Draws the lower bar in accordance with image count
void drawBar(RenderWindow&, int, int);

int main() {
    RenderWindow window(VideoMode(w, h), "Photo Album");
    window.setFramerateLimit(60);
    
    CLL images;

    Font font;
    if (!font.loadFromFile("FONT.ttf")) {
        return -1; // font not found
    }
    
    float pad = 10;
    
    // Main Box to display picture
    RectangleShape mainbox = setBox(pad + 60, pad, w - pad * 2 - 120, h - 80 - pad, grey, white, 2);
    
    // Previous Button
    float mainY = mainbox.getPosition().y + mainbox.getSize().y / 2.0f;
    RectangleShape prevbox = setBox(pad, mainY - 25, 50, 50, darkgrey, white, 2);
    Text prevBtn = setText("<", font, 36, pad + 25, mainY, white);
    
    // Next Button
    float mainR = mainbox.getPosition().x + mainbox.getSize().x;
    RectangleShape nextbox = setBox(mainR + 10, mainY - 25, 50, 50, darkgrey, white, 2);
    Text nextBtn = setText(">", font, 36, mainR + 10 + 25, mainY, white);
    
    // Add Button
    RectangleShape plusBox = setBox(w - 120, h - 60, 50, 50, darkgrey, white, 2);
    Text plusBtn = setText("+", font, 36, w - 120 + 25, h - 60 + 25, white);
    
    // Remove Button
    RectangleShape minusBox = setBox(w - 60, h - 60, 50, 50, darkgrey, white, 2);
    Text minusBtn = setText("-", font, 36, w - 60 + 25, h - 60 + 25, white);   
   
   // bottom bar
   RectangleShape bar = setBox(pad, h - 60, (w - 120) - pad * 2, 50, darkgrey, white, 2);

    window.clear(black);
    window.draw(mainbox);
    window.draw(prevbox);
    window.draw(prevBtn);
    window.draw(nextbox);
    window.draw(nextBtn);
    window.draw(bar);
    window.draw(plusBox);
    window.draw(plusBtn);
    window.draw(minusBox);
    window.draw(minusBtn);
    
    // Main loop or Game loop
    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) window.close();
            if (e.type == Event::MouseButtonPressed || e.type == Event::KeyPressed) {
  		        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                if (plusBox.getGlobalBounds().contains(mousePos) || e.key.code == Keyboard::Key::Space) {
                    cout << "Enter file location: ";
                    string name;
                    cin >> name;
                    images.addNode(name);
                }
                if (minusBox.getGlobalBounds().contains(mousePos) || e.key.code == Keyboard::Key::BackSpace) {
                    images.deleteNode();
                }
                if (prevbox.getGlobalBounds().contains(mousePos) || e.key.code == Keyboard::Key::Left) {
                    images.toPrev();
                }
                if (nextbox.getGlobalBounds().contains(mousePos) || e.key.code == Keyboard::Key::Right) {
                    images.toNext();
                }
            }
        }

        window.draw(mainbox);
        window.draw(images.getImage(window));
        window.draw(bar);
        drawBar(window, images.getCount(), images.getNow());
        window.display();
    }
}

RectangleShape setBox(float x, float y, float width, float height, Color fill, Color outline, float thickness) {
    RectangleShape box(Vector2f(width, height));
    box.setPosition(x, y);
    box.setFillColor(fill);
    box.setOutlineColor(outline);
    box.setOutlineThickness(thickness);
    return box;
}

Text setText(string str, Font &font, int size, float x, float y, Color fill) {
    Text text(str, font, size);
    FloatRect plusBounds = text.getLocalBounds();
    text.setOrigin(plusBounds.left + plusBounds.width / 2.0f, plusBounds.top + plusBounds.height / 2.0f);
    text.setPosition(x, y);
    text.setFillColor(fill);
    return text;
}

void drawBar(RenderWindow &win, int count, int curr) {
    if(!count) return;

    // Default box without bars
    if(count == 1) {
        win.draw(setBox(10, h - 60, (w - 120) - 10 * 2, 50, tint, blue, 0));
        return;
    }
    RectangleShape overlay = setBox(10, h - 60, (w - 120) - 10 * 2, 50, blue, blue, 0);
    win.draw(overlay);

    // Bars
    float x = 10, y = h - 60, dist = (w - 140) / count;
    for(int i = 1; i < count; i++) {
        win.draw(setBox(x + (i * dist) - 4, y, 8, 50, darkgrey, black, 0));
    }

    // Highlight image
    if(curr == 1) {
        win.draw(setBox(x + ((curr - 1) * dist), y, dist - 4, 50, tint, black, 0));
    }
    else if(curr == count) {
        win.draw(setBox(x + ((curr - 1) * dist) + 4, y, dist - 4, 50, tint, black, 0));
    }
    else
        win.draw(setBox(x + ((curr - 1) * dist) + 4, y, dist - 8, 50, tint, black, 0));
}

CLL::CLL() {
    count = 0;
    now = 0;
    head = NULL;
    current = NULL;
}

void CLL :: addNode(string name) {
    Texture image;
    Sprite img;
    if (!image.loadFromFile(name)) {
        cout << "Image loading failed!";
        return;
    }
    node *newNode = new node(image, img);
    if(!newNode) {
        cout << "Memory allocation failed" << endl;
        return;
    }
    if (!head) {
        head = newNode;
        newNode->next = head;
        newNode->prev = head;
        current = head;
        count = 1;
        now = 1;
        return;
    }
    newNode->next = head;
    newNode->prev = head->prev;
    head->prev->next = newNode;
    head->prev = newNode;
    count++;
    return;
}

void CLL :: deleteNode() {
    if(!head) {
        cout << "List is empty!\n";
        return;
    }

    if(head->next == head) {
        delete current;
        head = NULL;
        current = NULL;
        count = 0;
        now = 0;
        return;
    }

    if(current == head) {
        head = head->next;
    }

    node *temp = current;
    current->prev->next = current->next;
    current->next->prev = current->prev;
    current = current->next;
    delete temp;
    count--;
    if(now == count + 1) now = 1;
    
    return;
}

Sprite CLL :: getImage(RenderWindow &win) {
    if(current) return current->img;
    return Sprite();
}

void CLL :: toNext() {
    if(current) {
        current = current->next;
        now++;
        if(now == count + 1) now = 1;
    }
}

void CLL :: toPrev() {
    if(current) current = current->prev;
    now--;
    if(now == 0) now = count;
}

CLL :: ~CLL() {
    while(head) deleteNode();
}
