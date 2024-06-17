# Python 中的 do-while 範例

本專案展示了如何在 Python 中實現 `do-while` 迴圈。Python 並沒有內建的 `do-while` 迴圈，但我們可以使用 `while True` 迴圈和 `break` 語句來模擬這種行為。

## 實現方式

以下程式碼定義了一個 `do_while_example` 函數，用於輸出從 0 到 4 的計數：

```python
def do_while_example():
    count = 0
    while True:
        print(f"計數為: {count}")
        count += 1
        if not (count < 5):
            break

if __name__ == "__main__":
    do_while_example()
