import h5py
import numpy as np
import sys
import argparse

"""
Program očekuje da mu se proslede dva argumenta putem komandne linije:
1. Putanja do matrice koja se transponuje
2. Putanja do matrice sa rešenjem
Program učitava prvu matricu i transponuje je. 
Nakon toga, proverava da li se dobijeni rezultat poklapa sa rešenjem učitanim iz fajla prosleđenog kao drugi argument.
Program vraća True ili False u zavisnosti od rezultat poređenja
"""

parser = argparse.ArgumentParser(
    description='''Program proverava tačnost rezultata transponovanja prosleđene matrice.
        Kao argumente komandne linije treba proslediti putanju do hdf5 fajla matrice koja se transponuje, 
        kao i putanju do hdf5 fajla rezultata čija se ispravnost proverava. 
        Program će učitati prvu matricu, transponovati je, učitati drugu matricu i nakon toga je uporediti sa
        rezultatom transponovanja.'''
)
parser.add_argument('putanja_do_matrice', nargs=1, help='Putanja do hdf5 fajla matrice koja se transponuje.')
parser.add_argument('putanja_do_rezultata', nargs=1, help='Putanja do hdf5 fajla matrice rezultata čija se ispravnost proverava.')
args = parser.parse_args()

first_mat_path = sys.argv[1]
res_mat_path = sys.argv[2]

with h5py.File(first_mat_path, 'r') as f:
    first_np_mat = np.array(f['/dset'])
    
calculated_product_mat = np.transpose(first_np_mat)

with h5py.File(res_mat_path, 'r') as f:
    res_mat = np.array(f['/dset'])
    if np.array_equal(calculated_product_mat, res_mat):
        print('Provereni rezultat transponovanja je tačan.')
    else:
        print('Provereni rezultat transponovanja je netačan.')