# Huffman Tree generator
# @faustinoaq
# Jan, 2017
class Element
  property ch = [] of Element
  getter sym : Char, fr : Float64

  def initialize(@sym, @fr)
  end

  def +(e : Element)
    fr = @fr + e.@fr
    Element.new('*', fr)
  end
end

def huffman(elements)
  while elements.size > 2
    elements.sort_by! { |e| e.@fr }
    first = elements[0]
    second = elements[1]
    aux = first + second
    child = aux.ch
    child.push(first)
    child.push(second)
    2.times { elements.shift }
    elements.unshift(aux)
  end
  elements
end

BIN  = [] of Int32
CODE = {} of Char => String

def encode(tree : Array(Element))
  tree.each_with_index do |e, i|
    BIN << i
    if e.ch.empty?
      CODE[e.sym] = BIN.join
      BIN.pop
    else
      encode(e.ch)
    end
  end
  BIN.pop unless BIN.empty?
end

text = %(Premature optimization is the root of all evil.)
chars = {} of Char => Float64

def count_chars(text, chars)
  text.each_char do |c|
    if chars[c]?
      chars[c] += 1_f64
    else
      chars[c] = 1_f64
    end
  end
  chars
end

chars = count_chars(text, chars)
total = chars.values.sum
chars.each do |k, v|
  chars[k] = v/total
end

record Par, k : Char, v : Float64

def print_frequency(chars)
  chars.map do |k, v|
    Par.new(k, v)
  end.sort_by do |e|
    e.v
  end.each do |e|
    p [e.k, e.v]
  end
end

print_frequency(chars)

elements = [] of Element
chars.each do |k, v|
  elements << Element.new(k, v)
end
tree = huffman(elements)
encode(tree)
pp CODE

def print_encoded(text)
  encoded = ""
  text.each_char do |c|
    encoded += CODE[c]
  end
  pp encoded
  encoded
end

def print_decoded(encoded)
  bincode = CODE.invert
  limit = bincode.keys.map(&.size).max
  part = decoded = ""
  encoded.each_char do |c|
    part += c
    if bincode[part]?
      decoded += bincode[part]
      part = ""
    elsif part.size > limit
      raise "Invalid part of CODE"
    end
  end
  pp decoded
end

print_decoded(print_encoded(text))
