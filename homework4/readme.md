norace.c
在無互斥鎖版本中，由於多個執行緒同時訪問和修改共享資源（賬戶餘額），會發生競爭條件，導致最終的賬戶餘額不正確。這是因為不同執行緒的操作互相干擾，導致數據不一致。

race.c
在使用互斥鎖版本中，每個執行緒在訪問和修改共享資源時會獲取互斥鎖，確保同一時間只有一個執行緒可以進行操作。這樣可以避免競爭條件，確保數據的一致性和正確性。



