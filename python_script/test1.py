def devowel(word):
  return "".join('*' if c in 'aeiou' else c for c in word)

print(devowel("hel"))

