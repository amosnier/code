def complex_function1(parameters):
    field1 = parameters
    field2 = 0
    field3 = 'some initial value'
        
    def _help_function_1():
        nonlocal field2
        field2 = 'whatever'
    
    def _help_function_2():
        nonlocal field1, field3
        field3 = field1, 'something'

    _help_function_1()
    _help_function_2()
    print(field1, field2, field3)

def complex_function2(parameters):
    class state:
        field1 = parameters
        field2 = 0
        field3 = 'some initial value'
        
    def _help_function_1():
        state.field2 = 'whatever'
    
    def _help_function_2():
        state.field3 = state.field1, 'something'

    _help_function_1()
    _help_function_2()
    print(state.field1, state.field2, state.field3)

class complex_function3():
    def __init__(self, parameters):
        self.field1 = parameters
        self.field2 = 0
        self.field3 = 'some initial value'
        self._help_function_1()
        self._help_function_2()
        print(self.field1, self.field2, self.field3)
        
    def _help_function_1(self):
        self.field2 = 'whatever'
    
    def _help_function_2(self):
        self.field3 = self.field1, 'something'

def main():
    complex_function1('hello')
    complex_function2('hello')
    complex_function3('hello')

if __name__ == '__main__':
    main()
    
# hello whatever ('hello', 'something')
# hello whatever ('hello', 'something')
# hello whatever ('hello', 'something')
