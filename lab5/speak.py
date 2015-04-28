#! /bin/python
# coding: utf-8
conversion_espeak = [
("AO0","ɔ","&#596;","o"),
("AO","ɔ","&#596;","o"),
("AA","ɑ","&#593;","a"),
("AA0","ɑ","&#593;","a"),
("IY","i","i","i"),
("IY0","i","i","i"),
("UW","u","u","u"),
("EH","ɛ","&#603;","e"),
("EH0","ɛ","&#603;","e"),
("IH","ɪ","&#618;","aI"),
("IH0","ɪ","&#618;","aI"),
("UH","ʊ","&#650;","u"),
("UH0","ʊ","&#650;","u"),
("AH","ʌ","&#652;","a#"),
("AH1","ʌ","&#652;","^"),
("AH","ə","&#601;","a#"),
("AH0","ə","&#601;","a#"),
("AX","ə","&#601;","a#"),
("AX0","ə","&#601;","a#"),
("AE","æ","&#230;","@"),
("EY","eɪ","e&#618;","ei"),
("AY","aɪ","a&#618;","ai"),
("OW","oʊ","o&#650;","Ou"),
("AW","aʊ","a&#650;","au"),
("AW0","aʊ","a&#650;","au"),
("OY","ɔɪ","&#596;&#618;","oi"),
("ER","ɝ","&#605;",""),
("AXR","ɚ","&#602;",""),
("EH","ɛr","&#603;r","3:"),
("EH1","ɛr","&#603;r","3:"),
("UH","ʊr","&#650;r","u:"),
("UH1","ʊr","&#650;r","u:"),
("AO","ɔr","&#596;r","o:"),
("AO1","ɔr","&#596;r","o:"),
("AA","ɑr","&#593;r","a:"),
("AA1","ɑr","&#593;r","a:"),
("IH","ɪr","&#618;r","i:"),
("IH1","ɪr","&#618;r","i:"),
("IY","ɪr","&#618;r","i:"),
("IY1","ɪr","&#618;r","i:"),
("AW","aʊr","a&#650;r","au"),
("AW1","aʊr","a&#650;r","au"),
("P","p","p","p"),
("B","b","b","b"),
("T","t","t","t"),
("D","d","d","d"),
("K","k","k","k"),
("G","ɡ","&#609;","g"),
("CH","tʃ","t&#643;","tS"),
("JH","dʒ","d&#658;","dZ"),
("F","f","f","f"),
("V","v","v","v"),
("TH","θ","&#952;","th"),
("DH","ð","&#240;","TH"),
("S","s","s","s"),
("Z","z","z","z"),
("SH","ʃ","&#643;","S"),
("ZH","ʒ","&#658;","Z"),
("HH","h","h","h"),
("M","m","m","m"),
("EM","m̩","m&#809;","m"),
("N","n","n","n"),
("EN","n̩","n&#809;","n"),
("NG","ŋ","&#331;","N"),
("ENG","ŋ̍","&#331;&#781;","N"),
("L","ɫ","&#619;","l"),
("EL","ɫ̩","&#619;&#809;","l"),
("R","ɹ","&#633;","r"),
("DX","ɾ","&#638;","e"),
("NX","ɾ̃","&#638;&#771;","e"),
("Y","j","j","j"),
("W","w","w","w"),
("Q","ʔ","&#660;","q")]

import subprocess

def speak(output):
    list1 = output.split('\t')[1].split(' ')
    s = ""
    print list1
    for l in list1:
        for a in conversion_espeak:
            if a[0] == l:
                s = s + a[3]
                break
    return s

inp = raw_input()
s = speak(inp)
command = 'espeak -v en "[['+s+']]"'
print command
p = subprocess.Popen(command , shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
p.wait()