// Huffman Tree generator
// @faustinoaq
// Jun, 2017

#include <stdio.h>
#include <string>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

class Element {
  char sym;
  float fr;
  deque<Element*> child;
  public:
  Element(char sym, float fr) {
    this->sym = sym;
    this->fr = fr;
  }

  char get_sym() {
    return this->sym;
  }

  float get_fr() {
    return this->fr;
  }

  deque<Element*> get_child() {
    return this->child;
  }

  auto set_child(deque<Element*> child) {
    this->child = child;
  }

  auto add(Element* e) {
    fr = this->fr + e->get_fr();
    return new Element('*', fr);
  }
  
};

bool comp_fr(Element* a, Element* b) {
  return a->get_fr() < b->get_fr();
}

deque<Element*> huffman(deque<Element*> elements) {
  while (elements.size() > 2) {
    sort(elements.begin(), elements.end(), comp_fr);
    auto first = elements[0];
    auto last = elements[1];
    auto aux = first->add(last);
    auto child = aux->get_child();
    child.push_back(first);
    child.push_back(last);
    aux->set_child(child);
    elements.pop_front();
    elements.pop_front();
    elements.push_front(aux);
  }
  return elements; //tree
}
vector<int> BIN;
struct code {
  char sym;
  vector<int> bin;
};
vector<code> CODE;
void encode(deque<Element*> tree) {
  int i = 0;
  for (auto e : tree) {
    BIN.push_back(i);
    ++i;
    if (e->get_child().size() == 0) {
      struct code c;
      c.bin = BIN;
      c.sym = e->get_sym();
      CODE.push_back(c);
      BIN.pop_back();
    } else {
      encode(e->get_child());
    }
  }
  if (BIN.size() > 0) {
    BIN.pop_back();
  }
}

int main() {
  deque<Element*> elements;
  Element* e;
  // for (int i = 110; i < 120; ++i) {
  // e = new Element((char)i, (float)i);
  auto h = new Element('h', 0.1);
  auto o = new Element('o', 0.2);
  auto l = new Element('l', 0.1);
  auto a = new Element('a', 0.6);
  elements.push_back(h);
  elements.push_back(o);
  elements.push_back(l);
  elements.push_back(a);
  // }
  auto tree = huffman(elements);
  encode(tree);
  for (auto c : CODE) {
    printf("%c => ", c.sym);
    for (auto i : c.bin) {
      printf("%d", i);
    }
    printf("\n");
  }
  return 0;
}
