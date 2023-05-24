//
// Created by banoodle on 24.05.23.
//
#include "textbox.h"

void TextBox::set(Renderer *pRender, std::string label, int x, int y, bool Number) {
    onlyNumber = Number;
    this->pRender = pRender;
    t_cache = TextureCache::getCache(pRender);
    txtLabel = std::move(label);
    texLabel = t_cache->getText(txtLabel.c_str(), 18, {0, 0, 0, 255});

    SDL_QueryTexture(texLabel, nullptr, nullptr, &labelRect.w, &labelRect.h);
    labelRect.x = x;
    labelRect.y = y;
    inputFieldRect.x = labelRect.x + labelRect.w + 10;
    inputFieldRect.y = y - 5;
    inputFieldRect.h = labelRect.h + 10;
    inputFieldRect.w = max_length * 5 + 10;
    txtInput = "";
    inputTextRect.x = inputFieldRect.x + 5;
    inputTextRect.y = inputFieldRect.y + 5;
    inputTextRect.w = 0;
    inputTextRect.h = labelRect.h;
}

void TextBox::setMaxLength(int size) {
    max_length = size;
}

void TextBox::setText(std::string text) {
    txtInput = std::move(text);
    if (texInput != nullptr)
        SDL_DestroyTexture(texInput);
    texInput = t_cache->getText(txtInput.c_str(), 18, {0, 0, 0, 255});
    SDL_QueryTexture(texInput, nullptr, nullptr, &inputTextRect.w, &inputTextRect.h);
}

std::string TextBox::getText() {
    return txtInput;
}

int TextBox::getNumber() {
    return atoi(txtInput.c_str());
}

void TextBox::setNumber(int number) {
    txtInput = std::to_string(number);
    updateInput();
}

void TextBox::draw() {
    SDL_RenderCopy(pRender, texLabel, nullptr, &labelRect);
    SDL_SetRenderDrawColor(pRender, 255, 255, 255, 255); // white
    SDL_RenderFillRect(pRender, &inputFieldRect);
    SDL_SetRenderDrawColor(pRender, 0, 0, 0, 255); // black
    SDL_RenderDrawRect(pRender, &inputFieldRect);
    if (!txtInput.empty())
        SDL_RenderCopy(pRender, texInput, nullptr, &inputTextRect);
    if (selected) {
        if (blink > 20) {
            int curX1 = inputTextRect.x + inputTextRect.w;
            int curY2 = inputTextRect.y + inputTextRect.h;
            SDL_RenderDrawLine(pRender, curX1, inputTextRect.y, curX1, curY2);
        }
        blink = (blink + 1) % 40;

    }
}

void TextBox::fieldSelected(SDL_Event event) {
    bool right = event.motion.x > inputFieldRect.x;
    bool left = event.motion.x < inputFieldRect.x + inputFieldRect.w;
    bool over = event.motion.y < inputFieldRect.y + inputFieldRect.h;
    bool under = event.motion.y > inputFieldRect.y;
    std::cout << txtLabel << " check if selected " << std::endl;
    if (right && left && over && under) {
        selected = true;
        blink = 0;
        getInput();

    }
}

void TextBox::getInput() {
    std::cout << txtLabel <<" getInput" << std::endl;
    SDL_bool done = SDL_FALSE;
    SDL_StartTextInput();
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    done = SDL_TRUE;
                    break;
                case SDL_TEXTINPUT:
                    std::cout << "input detected" << event.text.text << std::endl;
                    if (onlyNumber) {
                        char buf[50] = "";
                        strcat(buf, event.text.text);
                        for (char c: buf) {
                            if (c >= '0' && c <= '9')
                                txtInput += c;
                        }
                    } else {
                        txtInput += event.text.text;
                    }
                    break;
                case SDL_KEYDOWN:
                    std::cout << "Key Pressed" << event.key.keysym.sym << std::endl;
                    if (event.key.keysym.sym == SDLK_BACKSPACE && !txtInput.empty())
                        txtInput.erase(txtInput.size() - 1);
                    if (event.key.keysym.sym == SDLK_KP_ENTER)
                        done = SDL_TRUE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    bool left = event.motion.x < inputFieldRect.x;
                    bool right = event.motion.x > inputFieldRect.x + inputFieldRect.w;
                    bool top = event.motion.y < inputFieldRect.y;
                    bool bottom = event.motion.y > inputFieldRect.y + inputFieldRect.h;
                    if (left || right || top || bottom) {
                        done = SDL_TRUE;
                    }
                    break;
            }
        }
        updateInput();
        draw();
        SDL_RenderPresent(pRender);
    }
    SDL_StopTextInput();
    selected = false;
}

TextBox::~TextBox() {
    if(texLabel != nullptr)
        SDL_DestroyTexture(texLabel);
    if(texInput != nullptr)
        SDL_DestroyTexture(texInput);
}

void TextBox::updateInput() {
    if (texInput != nullptr)
        SDL_DestroyTexture(texInput);
    texInput = t_cache->getText(txtInput.c_str(), 18, {0, 0, 0, 255});
    SDL_QueryTexture(texInput, 0, 0, &inputTextRect.w, &inputTextRect.h);
}

