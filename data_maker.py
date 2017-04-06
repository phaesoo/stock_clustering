# -*- coding:utf-8 -*-

import xlrd
import xlsxwriter
from yahoo_finance import Share

# read sp500 list file
read = xlrd.open_workbook("./sp500_list.xlsx");
read_sheet = read.sheet_by_index(0)

# excel 파일로 부터 snp500 리스트를 받아옴
snp500 = []
for row in range(read_sheet.nrows):
    if row == 0:
        continue
    snp500.append(read_sheet.cell(row, 0).value)

# 시작/끝 날짜지정
start_date = '2017-03-01'
end_date = '2017-04-04'

# 쓰기용 파일 생성
write = xlsxwriter.Workbook('./sp500_AdjCloseTemp.xlsx')
write_sheet = write.add_worksheet()

col = 0

for col_index, data in enumerate(snp500):
    if col_index != 157:
        continue

    col += 1

    stock = Share(data)
    history = stock.get_historical(start_date, end_date)

    # write data
    if col_index == 0:
        for index, date in enumerate(history):
            write_sheet.write(index + 1, 0, date['Date'])

    for index, some in enumerate(history):
        try:
            if index == 0:
                write_sheet.write(index, col , some['Symbol'])
            write_sheet.write(index + 1, col, float(some['Adj_Close']))
        except:
            continue

write.close()
