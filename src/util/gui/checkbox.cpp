//
// Created by banoodle on 15.04.23.
//

#include "checkbox.h"

void CheckBox::draw(bool highlighted) {
    if (highlighted)
        rh->setColor(_highlightedColor);
    else
        rh->setColor(_drawColor);
    rh->fillRect(&_rect);
    rh->rect(&_rect, 2, BLACK);
    rh->texture(_texText, &_rText);
}

bool CheckBox::isPointOnBtn(Point &p) const {
    bool xAxis = this->_rect.x <= p.x && this->_rect.x + this->_rect.w >= p.x;
    bool yAxis = this->_rect.y <= p.y && this->_rect.y + this->_rect.h >= p.y;
    return xAxis && yAxis;
}

bool CheckBox::clicked(SDL_Event e) {
    return clicked({e.motion.x,e.motion.y});
}


bool CheckBox::clicked(Point p) {
    if (isPointOnBtn(p)) {
        IfDebug{
            std::cout << "button " << _textArr << " clicked" << std::endl;
        }
        return true;
    }
    return false;
}


CheckBox::~CheckBox() {
    if (_texText != nullptr)
        SDL_DestroyTexture(_texText);
}

void CheckBox::entered(SDL_Event e) {
    entered({e.motion.x,e.motion.y});
}
void CheckBox::entered(Point p) {
    if (isPointOnBtn(p)) {
        _drawColor = _highlightedColor;
    } else {
        _drawColor = _buttonColor;
    }
}

CheckBox::CheckBox(const CheckBox &b) {
    strcpy_s(_textArr, b._textArr);
    IfDebug{
        std::cout << "using Copy Constructor: " << _textArr << std::endl;
    }
    this->_size = b._size;
    this->_rect = b._rect;
    this->_id = b._id;

    this->_buttonColor = b._buttonColor;
    this->_drawColor = b._drawColor;
    this->_highlightedColor = b._highlightedColor;
    this->_texText = t_cache->getText(_textArr, _size, &_rText);

    _rText.x = _rect.x + (_rect.w - _rText.w) / 2;
    _rText.y = _rect.y + (_rect.h - _rText.h) / 2;
}

void CheckBox::set(const string &label, int nSize, Rect nRect, int id, t_color btnColor) {
    this->_size = nSize;
    strcpy_s(_textArr, label.c_str());
    this->_rect = nRect;
    this->_buttonColor = RenderHelper::getColor(btnColor);
    this->_id = id;
    setHighlightedColor(&btnColor);

    this->_texText = t_cache->getText(_textArr, _size, &_rText);

    _rText.x = _rect.x + (_rect.w - _rText.w) / 2;
    _rText.y = _rect.y + (_rect.h - _rText.h) / 2;
    _drawColor = _buttonColor;
}

std::string CheckBox::getText() {
    return this->_textArr;
}

int CheckBox::getX() const {
    return _rect.x;
}

void CheckBox::setHighlightedColor(const t_color* high_color) {
    Color c;
    if(high_color == nullptr){
        c = _buttonColor;
        this->_highlightedColor.r = c.r + 20 <= 255 ? c.r + 20 : 255;
        this->_highlightedColor.g = c.g + 20 <= 255 ? c.g + 20 : 255;
        this->_highlightedColor.b = c.b + 20 <= 255 ? c.b + 20 : 255;
        this->_highlightedColor.a = c.a;
    }
    else{
        c = RenderHelper::getColor(*high_color);
        this->_highlightedColor = c;
    }
}
void CheckBox::setHighlightedColor(t_color high_color) {
    this->_highlightedColor = RenderHelper::getColor(high_color);
}


void CheckBox::setSize(SDL_Rect nRect) {
    this->_rect = nRect;
    _rText.x = _rect.x + (_rect.w - _rText.w) / 2;
    _rText.y = _rect.y + (_rect.h - _rText.h) / 2;
}

void CheckBox::setColor(t_color color) {
    this->_buttonColor = RenderHelper::getColor(color);
}

CheckBox::CheckBox(const string &label, int size, Rect rect, int id, t_color btn_color) {
    set(label, size,rect,id,btn_color);
}

int CheckBox::getId() const {
    return _id;
}

CheckBox::CheckBox(const string &label, int size, int id, t_color btn_color) {
    set(label, size, {},id,btn_color);
}
