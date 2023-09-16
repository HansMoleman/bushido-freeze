

def decToHex(decval):
    values = []
    
    if(decval == 0):
        return str(0)
    else:
        quo = int(decval // 16)
        rem = int(decval % 16)

        while(not((quo == 0) and (rem == 0))):
            hexv = ""

            if(rem == 10):
                hexv = "A"
            elif(rem == 11):
                hexv = "B"
            elif(rem == 12):
                hexv = "C"
            elif(rem == 13):
                hexv = "D"
            elif(rem == 14):
                hexv = "E"
            elif(rem == 15):
                hexv = "F"
            else:
                hexv = str(rem)
            values.append(hexv)

            rem = int(quo % 16)
            quo = int(quo // 16)
        #values.append("0")

        hexstr = ""
        i = len(values) - 1
        while(0 <= i):
            hexstr += values[i]
            i -= 1

        return hexstr

