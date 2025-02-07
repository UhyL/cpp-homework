#include "TextEditor.h"
#include <iostream>

using namespace std;

TextEditor::TextEditor() {
    // TODO: 用空文本初始化
    this->cursor = this->text.begin();
    this->copy_text.clear();
};

void TextEditor::addText(const string &text) {
    // TODO: 将 text 添加到光标所在位置
    for (char c : text) {
        this->text.insert(this->cursor, c);
        // ++this->cursor;
    }
}

void TextEditor::deleteText(int length) {
    // TODO: 删除光标左边 length 个字符
    for (int i = 0; i < length && this->cursor != this->text.begin(); ++i) {
        --this->cursor;
        this->cursor = this->text.erase(this->cursor);
    }
}

void TextEditor::moveCursor(int steps) {
    // TODO: 将光标向左向右移动
    if (steps > 0) {
        for (int i = 0; i < steps && this->cursor != this->text.end(); ++i)
            ++this->cursor;
    } else {
        for (int i = 0; i > steps && this->cursor != this->text.begin(); --i)
            --this->cursor;
    }
}

void TextEditor::copy(int length) {
    // TODO: 复制光标左侧 length 个字符
    auto it = this->cursor;
    this->copy_text.clear();
    if (length == 0) return;
    for (int i = 0; i < length && it != this->text.begin(); ++i)
        --it;
    while (it != this->cursor) {
        this->copy_text.push_back(*it);
        ++it;
    }
}

void TextEditor::paste() {
    // TODO: 在光标处添加上一次复制的文本
    for (char c : copy_text) {
        this->text.insert(this->cursor, c);
    }
}

void TextEditor::print() {
    // TODO: 输出当前编辑器内容
    for (auto it = text.begin(); it != text.end(); ++it) {
        cout << *it;
    }
    cout << endl;
}