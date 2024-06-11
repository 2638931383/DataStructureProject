import openpyxl
import requests
import json

from openpyxl import Workbook
wb = openpyxl.load_workbook("university.xlsx")

sheet1 = wb.get_sheet_by_name("openpyxl")
prj = sheet1.columns
prjTuple = tuple(prj)
for cell in prjTuple[0]:
        workbook = Workbook()
        sheet = workbook.active  # 激活sheet
        sheet.title = "openpyxl"  # 设置sheet名字
        sheet.append(["Name", "Longitude", "Latitude" , "Type"])  # 插入标题
        for j in range (1 , 9) :
            url = f'https://restapi.amap.com/v3/place/text?key=909362f9b134098a82fbeee3d686f120&keywords={cell.value}&types=&city=北京&children=&offset=25&page={j}&extensions=all'
            res = requests.get(url , timeout = 30)
            data = res.json()
            if data['status'] == '1':
                for i in range(0, len(data['pois']) - 1):
                    #list = []
                    name = str(data['pois'][i]['name'])
                    location = str(data['pois'][i]['entr_location'])
                    if location == "[]" :
                        location = str(data['pois'][i]['location'])
                    list = location.split(",")
                    type = str(data['pois'][i]['type'])
                    list.insert(0 , name)
                    #list.append(location)
                    list.append(type)
                    sheet.append(list)
                    workbook.save(f"{cell.value}.xlsx")