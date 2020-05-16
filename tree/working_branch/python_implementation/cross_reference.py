#!/usr/bin/env python3.8

# trying to implement the code in a simpler language
from pprint import pprint as pp

class node():
    def __init__(self, word: str):
        self.word = word
        self.count = 0
        self.line_numbers = []
    def __repr__(self):
        list_str = ', '.join(str(x) for x in self.line_numbers)
        return "(word: {}, count: {}, line_numbers: [{}])".format(
        self.word, self.count, list_str
      )

def is_comment(string: str):
    if(len(string) == 0): return False
    elif(string[0] == "/"): return True
    return is_multiline_comment(string) or False

def is_multiline_comment(string: str):
    return (string[0] == "/" and string[1] == "*")

def remove_non_alpha(string: str):
    s = ""
    in_quotes = False
    for c in string:
      if(c.isalpha() and not in_quotes): s+=c
      elif(c == "\""): in_quotes = True
      elif(c == "\"" and in_quotes == True): in_quotes = False
      else: s+=" "
    return s

with open("example.c") as c_file:
    # need to make strip -> remove extra spaces
    # need to make replace -> replace newline with nothing
    contents = c_file.readlines()
    contents = [element.replace("\n", "").strip() for element in contents]

in_comment = False
container = {}

for i, element in enumerate(contents):
  if(is_comment(element)):
    if(is_multiline_comment(element) and "*/" not in element):
      in_comment = True
  elif(element and element[0].isalpha() and not in_comment):
    string = remove_non_alpha(element)
    for s in string.split():
      if(s not in container):
        container[s] = node(s)
      container[s].count+=1
      container[s].line_numbers.append(i+1)

  if("*/" in element):
    # use strstr to check if the substring is in a string
    in_comment = False

for key, value in sorted(container.items(), key=lambda x: x[0]): 
    print("{} : {}".format(key, value))
