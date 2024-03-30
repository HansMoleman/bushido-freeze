
###
#
#
#
##



def convert(src_path):
    file_in = open(src_path, 'r')
    line_in = file_in.readline()
    data = []

    while(not(line_in == '' or line_in == '\n')):
        line_arr = line_in.strip().split(", ")

        for val in line_arr:
            hexval = val.strip(',')
            hexval = hexval[2:-1]
            intval = int(hexval, 16)
            binval = "{0:b}".format(intval)

            while(len(binval) < 32):
                binval = f"0{binval}"

            data.append(binval)

        line_in = file_in.readline()
    file_in.close()

    out_str = ""
    for value in data:
        out_str += f"{value}\n"

    fname = f"{src_path[:-8]}.bin"
    file_out = open(fname, 'w')
    file_out.write(out_str)
    file_out.close()