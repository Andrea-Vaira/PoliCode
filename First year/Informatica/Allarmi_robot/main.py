import csv
strutturaFile = []
robots = []

def getIds(robots):
    lista = []
    for item in robots:
        lista.append(item['idRobot'])
    return lista

def getDataFromFile():
    file = open('allarmi.csv', 'r')
    reader = csv.DictReader(file, delimiter=';')

    for row in reader:
        strutturaFile.append(row)
    file.close()

def createStructRobot():
    for alert in strutturaFile:
        if alert['fk_id_robot'] not in getIds(robots):
            robots.append({'idRobot':alert['fk_id_robot'], 'nAlert':1})
        else:
            for r in robots:
                if r['idRobot'] == alert['fk_id_robot']:
                    r['nAlert'] = r['nAlert'] + 1


def printResult():
    for r in robots:
        print(f"{r['idRobot']}      {r['nAlert']}")

def findMaxSeverity():
    strutturaFile.sort(key = lambda p: int(p['severity']), reverse=True)
    lista = []
    for r in strutturaFile:
        if r['severity'] == strutturaFile[0]['severity'] and r['fk_id_robot'] not in lista:
            lista.append(r['fk_id_robot'])
    return (strutturaFile[0]['severity'], lista)
            


def main():
    getDataFromFile()
    createStructRobot()
    robots.sort(key = lambda p: p['nAlert'], reverse=True)
    printResult()

    mySet = findMaxSeverity()
    print(f'Max severity: {mySet[0]}')
    for id in mySet[1]:
        print(id)


main()