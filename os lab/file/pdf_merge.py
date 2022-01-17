from PyPDF2 import PdfFileMerger
import os
from glob import glob  

file_list=glob('*.pdf',)
file_list.sort(key=lambda x : int(x[21]) if x[22]=='.' else int(x[21:23]))
print(file_list)
merger=PdfFileMerger()

for file in file_list:
    merger.append(file)

merger.write("Tanmay Vig_19BCS061.pdf")
merger.close()

