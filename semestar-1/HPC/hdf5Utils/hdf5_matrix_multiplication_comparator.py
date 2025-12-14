import h5py
import numpy as np
import sys
import argparse

"""
Program očekuje da mu se proslede tri argumenta putem komandne linije:
1. Putanja do prve matrice
2. Putanja do druge matrice
3. Putanja do matrice sa proizvodom
Program učitava prve dve matrice i množi ih. 
Nakon toga, proverava da li se dobijeni rezultat poklapa sa proizvodom učitanim iz fajla prosleđenog kao treći argument.
Program vraća True ili False u zavisnosti od rezultat poređenja
"""

parser = argparse.ArgumentParser(
    description='''Program proverava tačnost rezultata množenja prosleđenih matrica.
        Kao argumente komandne linije treba proslediti putanje do hdf5 fajlova matrica koje se množe, 
        kao i putanju do hdf5 fajla rezultata čija se ispravnost proverava. 
        Program će učitati prve dve matrice, pomnožiti ih, učitati treću matricu i nakon toga je uporediti sa
        rezultatom množenja prve dve.'''
)
parser.add_argument('putanja_do_matrice_1', nargs=1, help='Putanja do hdf5 fajla matrice prvog činioca.')
parser.add_argument('putanja_do_matrice_2', nargs=1, help='Putanja do hdf5 fajla matrice drugog činioca.')
parser.add_argument('putanja_do_rezultata', nargs=1, help='Putanja do hdf5 fajla matrice rezultata čija se ispravnost proverava.')
args = parser.parse_args()

first_mat_path = sys.argv[1]
second_mat_path = sys.argv[2]
product_mat_path = sys.argv[3]

with h5py.File(first_mat_path, 'r') as f:
    first_np_mat = np.array(f['/dset'])

with h5py.File(second_mat_path, 'r') as f:
    second_np_mat = np.array(f['/dset'])
    
calculated_product_mat = np.matmul(first_np_mat, second_np_mat)

with h5py.File(product_mat_path, 'r') as f:
    product_mat = np.array(f['/dset'])
    if np.array_equal(calculated_product_mat, product_mat):
        print('Provereni rezultat množenja je tačan.')
    else:
        print('Provereni rezultat množenja je netačan.')