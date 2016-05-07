
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

#for i in range(1,len(finalDocs)):
# root.append(finalDocs[i])
#print(root)
root=['E:/Study/Test/stripe-java-master/target/site/clover/com',
'E:/Study/Test/twilio-java-master/target/site/clover/com',
'E:/Study/Test/unirest-java-master/target/site/clover/com']
for rooot in root:
#rooot='E:/Study/Test/sonar-java-master/target/site/clover/org'
 outname=rooot.split('Test/')[1].split('/')[0]
 split=rooot.split('clover/')[1]
 AllDocuments=[]                                  ##paths of all files(html and js)
 for parent,dirnames,filenames in os.walk(rooot):
    for filename in filenames:
      if "Test" not in filename:
        path=parent+'/'+filename
        AllDocuments.append(path.replace('//','/'))  ##paths of all files(html and js)    



 AllStatements=[]   #row

 TestMethodName=[]   ##no duplicate  column
 PassorFail=[]

 allid=[]            #test ID
 allname=[]          ## Test method has duplicate

 for document in AllDocuments: 
  if '.html' in document:
     file=open(document,'r',encoding='ISO-8859-1')
     data=file.read().split('tr id="test-')
     if len(data)>1:
         for i in range(1,len(data)):
             id=data[i].split('">')[0]
             TestName=data[i].split('"sortValue">')[2].split('</span>')[0]
             if id not in allid:
              allid.append(id)
              allname.append(TestName) 
             if TestName not in TestMethodName:
                 TestMethodName.append(TestName)
  if '.js' in document:
     path=document.split(split)[1].split('.')[0]
     file=open(document,'r',encoding='ISO-8859-1')
     data=file.read().split('clover.testTargets = {')[1]
     if '"statements":[' in data:
         Statements=data.split('"statements":[')
         for i in range(1,len(Statements)):
           Statement=Statements[i].split(']},"test')[0].split(',')
           for j in Statement:
            if '{"sl":' in j:
             OneStatement=j.split('{"sl":')[1].split('}')[0]   ###(34,45,345,34566...)
             OneStatement=path+":::"+OneStatement
             if OneStatement not in AllStatements:
               AllStatements.append(OneStatement)
     file.close()
 slength=len(AllStatements)     #length of all statements
 tlength=len(TestMethodName)
 print(slength)
 print(tlength)

 print(slength)
 Matrix=[['0' for col in range(slength)] for row in range(tlength)]
 for document in AllDocuments:
  if '.js' in document :
     path=document.split(split)[1].split('.')[0]
     file=open(document,'r',encoding='ISO-8859-1')
     data=file.read().split('clover.testTargets = {')[1]
      
     TestNumbers=data.split(',"test_')
     for i in range(1,len(TestNumbers)):
      OneNumber=TestNumbers[i].split('":{"')[0]
      index=allid.index(OneNumber)
      Onetestmethod=allname[index]
      indexT=TestMethodName.index(Onetestmethod)
      Statements=TestNumbers[i].split('"statements":[')
      for i in range(1,len(Statements)):
        Statement=Statements[i].split(']},"test')[0].split(',')
        for j in Statement:
         if '{"sl":' in j:
          OneStatement=j.split('{"sl":')[1].split('}')[0]   ###(34,45,345,34566...)
          OneStatement=path+":::"+OneStatement
          indexS=AllStatements.index(OneStatement)
          Matrix[indexT][indexS]='1'
 outmatrix='E:/Study/Test/output/'+outname+'Matrx'
 outmatri=open(outmatrix,'a')
 outtest='E:/Study/Test/output/'+outname+'Tests'
 outT=open(outtest,'a')
 print(outname)

 for i in Matrix:
  for j in i:
   outmatri.write(j)
   outmatri.write(' ')
  outmatri.write('\n')
 for i in TestMethodName:
  outT.write(i)
  outT.write('\n')
 