class f:
    def __init__(self):
        self._x = 0
        self._g()
        self._h()
        print(self._x)
    def _g(self):
        self._x = 1
    def _h(self):
        x = 2
f() # 1
