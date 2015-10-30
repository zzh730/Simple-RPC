from xml.dom.minidom import parse
import xml.dom.minidom


DOMTree = xml.dom.minidom.parse("abc.xml")
collection = DOMTree.documentElement
programes = collection.getElementsByTagName("program")

procedure = collection.getElementsByTagName("procedure")

for p in programes:
    num_id = p.getElementsByTagName('numeric_id')
    version = p.getElementsByTagName('version')

function = []
for f in procedure:
    temp ={}
    temp['name'] = f.getElementsByTagName("name")
    temp['numeric_id'] = f.getElementsByTagName("id")
    temp['type'] = f.getElementsByTagName('return')
    temp['param'] = []
    param = f.getElementsByTagName('param')

