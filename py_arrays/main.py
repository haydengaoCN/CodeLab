input = 'input'
out = 'result'
fin = open(input, 'r')
lines = fin.readlines()
fout = open(out, 'w')

out_array = []
for line in lines:
    line_list = line.split()
    print line_list
    str1 = "{" + "\"" + line_list[0] + "\"" + ", "
    str2 = line_list[1][:-1] + "}" + ",\n"
    print str1, str2
    out_array.append('  ' + str1 + str2)
for line in out_array:
    fout.write(line)

fin.close()
fout.close()