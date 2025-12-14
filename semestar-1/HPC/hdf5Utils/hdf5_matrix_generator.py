import h5py
import numpy as np
import sys
import argparse

"""
Program očekuje da mu se proslede N i M kao argumenti komandne linije.
N - broj vrsta
M - broj kolona
Nakon toga, program generiše matricu nasumičnih vrednosti veličine NxM.
Matrica će biti sačuvana u fajlu nazvanom po šablonu:
    m<N>x<M>.h5, gde će <N> i <M> biti zamenjeni odgovarajućim dimenzijama matrice.
"""

parser = argparse.ArgumentParser(
    description='''Program generiše matricu čija je veličina jednaka prosleđenim argumentima.
        Generisana matrica biće smeštena u direktorijum u kom se nalazi i ova skripta, u datoteku sa nazivom m<N>x<M>.h5,
        gde će <N> i <M> biti zamenjeni odgovarajućim dimenzijama matrice.'''
)
parser.add_argument('N', nargs=1, help='Broj vrsta generisane matrice.')
parser.add_argument('M', nargs=1, help='Broj kolona generisane matrice')
args = parser.parse_args()

N = sys.argv[1]
M = sys.argv[2]
print(f'Generisanje matrice veličine {N}x{M}')
if not N.isnumeric() or not M.isnumeric():
    print('Neuspešno generisanje matrice: Parametri N i M moraju biti celi brojevi!')
    exit(-1)

mat = np.random.randint(low=1, high=50, size = (int(N), int(M)))
file_name = f'm{N}x{M}.h5'

with h5py.File(file_name, 'w') as f:
    dset = f.create_dataset("/dset", data=mat)

print(f'Matrica sačuvana u datoteci pod nazivom {file_name}')
