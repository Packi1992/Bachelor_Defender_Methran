//
// Created by banoodle on 15.04.23.
//

#include "Button.h"

void Button::Render(bool highlighted) {
    if (_blend) {
        rh->fillRect(&_rect, highlighted?_highlightedColor:_drawColor, 180);
    } else {
        if (highlighted)
            rh->setColor(_highlightedColor);
        else
            rh->setColor(_drawColor);
        rh->fillRect(&_rect);
    }
    rh->rect(&_rect, _blend?0:2, BLACK);

    // Text Render
    rh->blendTexture(_texText,&_rText);
    //rh->texture(_texText, &_rText);
}

bool Button::isPointOnBtn(Point &p) const {
    bool xAxis = this->_rect.x <= p.x && this->_rect.x + this->_rect.w >= p.x;
    bool yAxis = this->_rect.y <= p.y && this->_rect.y + this->_rect.h >= p.y;
    return xAxis && yAxis;
}

bool Button::clicked(SDL_Event e) {
    return clicked({e.motion.x, e.motion.y});
}


bool Button::clicked(Point p) {
    if (isPointOnBtn(p)) {
        IfDebug {
            std::cout << "button " << _textArr << " clicked" << std::endl;
        }
        return true;
    }
    return false;
}


Button::~Button() {
    if (_texText != nullptr)
        SDL_DestroyTexture(_texText);
}

void Button::entered(SDL_Event e) {
    entered({e.motion.x, e.motion.y});
}

void Button::entered(Point p) {
    if (isPointOnBtn(p)) {
        _drawColor = _highlightedColor;
    } else {
        _drawColor = _buttonColor;
    }
}

Button::Button(const Button &b) {
    strcpy(_textArr, b._textArr);
    this->_size = b._size;
    this->_rect = b._rect;
    this->_id = b._id;
    this->_blend = b._blend;
    this->_buttonColor = b._buttonColor;
    this->_drawColor = b._drawColor;
    this->_highlightedColor = b._highlightedColor;
    this->_texText = t_cache->getBlendedText(_textArr, _size, &_rText);

    _rText.x = _rect.x + (_rect.w - _rText.w) / 2;
    _rText.y = _rect.y + (_rect.h - _rText.h) / 2;
}

void Button::set(const string &label, int nSize, Rect nRect, int id, t_color btnColor, bool blend) {
    this->_size = nSize;
    strcpy(_textArr, label.c_str());
    this->_rect = nRect;
    this->_buttonColor = RenderHelper::getColor(btnColor);
    this->_id = id;
    setHighlightedColor(&btnColor);
    this->_blend = blend;
    this->_texText = t_cache->getBlendedText(_textArr, _size, &_rText);

    _rText.x = _rect.x + (_rect.w - _rText.w) / 2;
    _rText.y = _rect.y + (_rect.h - _rText.h) / 2;
    _drawColor = _buttonColor;
}

std::string Button::getText() {
    return this->_textArr;
}

int Button::getX() const {
    return _rect.x;
}

void Button::setHighlightedColor(const t_color *high_color) {
    Color c;
    if (high_color == nullptr) {
        c = _buttonColor;
        this->_highlightedColor.r = c.r + 20 <= 255 ? c.r + 20 : 255;
        this->_highlightedColor.g = c.g + 20 <= 255 ? c.g + 20 : 255;
        this->_highlightedColor.b = c.b + 20 <= 255 ? c.b + 20 : 255;
        this->_highlightedColor.a = c.a;
    } else {
        c = RenderHelper::getColor(*high_color);
        this->_highlightedColor = c;
    }
}

void Button::setHighlightedColor(t_color high_color) {
    this->_highlightedColor = RenderHelper::getColor(high_color);
}


void Button::setSize(SDL_Rect nRect) {
    this->_rect = nRect;
    _rText.x = _rect.x + (_rect.w - _rText.w) / 2;
    _rText.y = _rect.y + (_rect.h - _rText.h) / 2;
}

void Button::setColor(t_color color) {
    this->_buttonColor = RenderHelper::getColor(color);
}

Button::Button(const string &label, int size, Rect rect, int id, t_color btn_color, bool blend) {
    set(label, size, rect, id, btn_color, blend);
}

int Button::getId() const {
    return _id;
}

Button::Button(const string &label, int size, int id, t_color btn_color, bool blend) {
    set(label, size, {}, id, btn_color, blend);
}
