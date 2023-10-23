import sys
sys.path.append('./build/lib.linux-x86_64-3.10')
import dimensions as dims
import fraction as frac

def test_import():
    print(dims)
    print(dims.system('ls -l'))

    dims.save("hello")
    assert dims.load() == "hello"
    
    mfrac = frac.Fraction()