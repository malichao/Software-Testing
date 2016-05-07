
import os
import sys


root='E:\Study\Test'
#root=sys.argv[1]
#outname=sys.argv[1].split('Test/')[1].split('/')[0]
#split=root.split('clover/')[1]

AllDocuments=[]                                  ##paths of all files(html and js)
for parent,dirnames,filenames in os.walk(root):
    for filename in filenames:
      if "Test" not in filename:
        path=parent+'/'+filename
        path=path.replace('\\','/')
        if 'site' in path and 'clover/aui' not in path and 'clover/clover' not in path and 'clover/img' not in path:
          AllDocuments.append(path)

AllDoc=[]
for i in AllDocuments:
 path=i.split('clover/')
 if len(path)>1:
  if len(path[1].split('/'))>1:
   latter=path[1].split('/')[0]
   fullpath=path[0]+'clover/'+latter
   if fullpath not in AllDoc:
    AllDoc.append(fullpath)

finalDocs=[]
for i in AllDoc:
 if 'target'==i.split('/')[4]:
  finalDocs.append(i)
root=[]

for i in range(1,len(finalDocs)):
 root.append(finalDocs[i])
 print(finalDocs[i])
 
  

 


