KeyWords = ['for', 'if']
Brackets = ['{']
one_space = ' '

def process_key_words_space(curline_str, KeyWords):
  for kw in KeyWords:
    key = kw + '('
    idx = curline_str.find(key)
    if idx != -1:
      curline_str = curline_str[:idx+len(kw)] + one_space + curline_str[idx+len(kw):]

  # {
  idx = curline_str.find('{')
  if idx == -1:
    return curline_str
  if idx > 0 and curline_str[idx-1] != one_space:
    curline_str = curline_str[:idx] + one_space + curline_str[idx:]
  return curline_str

str1 = 'for(auto'
str2 = 'if(x < 0)'
str3 = 'for ( auto idx = 0'
str4 = 'void foo(){'
process_key_words_space(str1, KeyWords)
process_key_words_space(str2, KeyWords)
process_key_words_space(str3, KeyWords)
process_key_words_space(str4, KeyWords)
