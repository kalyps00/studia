import ctypes
import os
import subprocess

#Szyfr_RSA.c
class int1024(ctypes.Structure):
	_fields_ = [
		('chunk',ctypes.c_ulonglong*66),
	]
class public_key(ctypes.Structure):
	_fields_ = [
		('e',int1024),
		('n',int1024),
	]
class private_key(ctypes.Structure):
	_fields_ = [
		('d',int1024),
		('n',int1024),
	]
class key(ctypes.Structure):
	_fields_ = [
		('publickey',public_key),
		('privatekey',private_key),
	]
class Montgomery_pack(ctypes.Structure):
	_fields_ = [
		('R_wykladnik',ctypes.c_int),
		('R',int1024),
		('R_',int1024),
		('N',int1024),
		('M',int1024),
	]
class pair_int1024(ctypes.Structure):
	_fields_ = [
		('fi',int1024),
		('se',int1024),
	]
class pair_int(ctypes.Structure):
	_fields_ = [
		('fi',ctypes.c_int),
		('se',ctypes.c_int),
	]
class vec_pair_int(ctypes.Structure):
	_fields_ = [
		('rozm',ctypes.c_int),
		('rozm_max',ctypes.c_int),
		('wsk',ctypes.POINTER(pair_int)),
	]
class c_string(ctypes.Structure):
	_fields_ = [
		('rozm',ctypes.c_int),
		('rozm_max',ctypes.c_int),
		('wsk',ctypes.c_char_p),
	]
#biblioteka.c
class TextStats(ctypes.Structure):
	_fields_ = [
		('liczba_znakow',ctypes.c_int),
		('liczba_liter',ctypes.c_int),
		('liczba_wyrazow',ctypes.c_int),
		('liczba_zdan',ctypes.c_int),
		('liczba_akapitow',ctypes.c_int),
		('liczba_znakow_specjalnych',ctypes.c_int),
		('liczba_cyfr',ctypes.c_int),
		('min_dlugosc_slowa',ctypes.c_int),
		('max_dlugosc_slowa',ctypes.c_int),
		('srednia_dlugosc_slowa',ctypes.c_float),
		('srednia_dlugosc_zdania',ctypes.c_float),
		('zlozonosc_leksykalna',ctypes.c_float),
		('tablica_liter',ctypes.c_int*52),
	]


#Szyfr_RSA.c
def szyfr_rsa_init():
	nazwa = 'Szyfr_RSA'

	if os.name == 'posix':
		compile_command = [
			"gcc",
			"-shared",
			"-fPIC",
			nazwa+'.c',
			"-o",
			nazwa+'.so'
			]
		try:
			subprocess.run(compile_command, check=True)
		except:
			print("Cos poszlo zle :( Upewnij sie ze masz zainstalowane gcc")
			exit()
		lib = ctypes.CDLL("./"+nazwa+".so")
	elif os.name == 'nt':
			try:
					os.environ['PATH'] = r'C:\msys64\mingw64\bin;' + os.environ['PATH']
					subprocess.run(['gcc', '-shared', nazwa+'.c', '-o', nazwa + '.dll'], check=True)
			except:
					print("Cos poszlo zle :( Upewnij sie ze masz zainstalowane gcc")
					exit()
			lib = ctypes.CDLL('./'+nazwa+'.dll')
	#kod z konwerter.py

	
	lib.multiply.restype = int1024
	lib.multiply.argtypes = [int1024,int1024]
	lib.shift.restype = int1024
	lib.shift.argtypes = [int1024,ctypes.c_int]
	lib.right_shift.restype = int1024
	lib.right_shift.argtypes = [int1024,ctypes.c_int]
	lib.get_bits.restype = ctypes.c_int
	lib.get_bits.argtypes = [int1024]
	lib.subtract.restype = int1024
	lib.subtract.argtypes = [int1024,int1024]
	lib.add.restype = int1024
	lib.add.argtypes = [int1024,int1024]
	lib.isGreaterOrEqual.restype = ctypes.c_bool
	lib.isGreaterOrEqual.argtypes = [ctypes.POINTER(int1024),ctypes.POINTER(int1024)]
	lib.bitshift.restype = int1024
	lib.bitshift.argtypes = [int1024,ctypes.c_ulonglong]
	lib.right_bitshift.restype = int1024
	lib.right_bitshift.argtypes = [int1024,ctypes.c_ulonglong]
	lib.fast_divide_by_two.restype = int1024
	lib.fast_divide_by_two.argtypes = [int1024]
	lib.count_zeroes.restype = ctypes.c_int
	lib.count_zeroes.argtypes = [int1024]
	lib.modulo.restype = int1024
	lib.modulo.argtypes = [int1024,int1024]
	lib.division_with_modulo.restype = pair_int1024
	lib.division_with_modulo.argtypes = [int1024,int1024]
	lib.random_int1024_v.restype = int1024
	lib.random_int1024_v.argtypes = []
	lib.random_int1024.restype = int1024
	lib.random_int1024.argtypes = [int1024]
	lib.isEqual.restype = ctypes.c_bool
	lib.isEqual.argtypes = [int1024,int1024]
	lib.init_vec_pair_int.restype = None
	lib.init_vec_pair_int.argtypes = [ctypes.POINTER(vec_pair_int)]
	lib.push_vec_pair_int.restype = None
	lib.push_vec_pair_int.argtypes = [ctypes.POINTER(vec_pair_int),ctypes.c_int,ctypes.c_int]
	lib.free_vec_pair_int.restype = None
	lib.free_vec_pair_int.argtypes = [ctypes.POINTER(vec_pair_int)]
	lib.top_vec_pair_int.restype = pair_int
	lib.top_vec_pair_int.argtypes = [ctypes.POINTER(vec_pair_int)]
	lib.pop_vec_pair_int.restype = None
	lib.pop_vec_pair_int.argtypes = [ctypes.POINTER(vec_pair_int)]
	lib.Binary_Euclidean_Algorithm.restype = pair_int1024
	lib.Binary_Euclidean_Algorithm.argtypes = [int1024,int1024]
	lib.fast_divide.restype = int1024
	lib.fast_divide.argtypes = [int1024,ctypes.c_int]
	lib.fast_modulo.restype = int1024
	lib.fast_modulo.argtypes = [int1024,ctypes.c_int]
	lib.init_Montgomery_algorithm.restype = Montgomery_pack
	lib.init_Montgomery_algorithm.argtypes = [int1024,ctypes.c_int]
	lib.ConvertToMontgomeryForm.restype = int1024
	lib.ConvertToMontgomeryForm.argtypes = [int1024,Montgomery_pack]
	lib.ConvertFromMontgomeryForm.restype = int1024
	lib.ConvertFromMontgomeryForm.argtypes = [int1024,Montgomery_pack]
	lib.REDC.restype = int1024
	lib.REDC.argtypes = [int1024,Montgomery_pack]
	lib.fast_montgomery_exponentation.restype = int1024
	lib.fast_montgomery_exponentation.argtypes = [int1024,int1024,int1024,Montgomery_pack]
	lib.RabinMiller.restype = ctypes.c_bool
	lib.RabinMiller.argtypes = [int1024,ctypes.c_int]
	lib.RSA.restype = key
	lib.RSA.argtypes = []
	lib.init_c_string.restype = None
	lib.init_c_string.argtypes = [ctypes.POINTER(c_string)]
	lib.push_c_string.restype = None
	lib.push_c_string.argtypes = [ctypes.POINTER(c_string),ctypes.c_char]
	lib.free_c_string.restype = None
	lib.free_c_string.argtypes = [ctypes.POINTER(c_string)]
	lib.get_c_string.restype = ctypes.c_char
	lib.get_c_string.argtypes = [ctypes.POINTER(c_string),ctypes.c_int]
	lib.RSA_encode.restype = None
	lib.RSA_encode.argtypes = [ctypes.POINTER(c_string),public_key,ctypes.POINTER(c_string)]
	lib.RSA_decode.restype = None
	lib.RSA_decode.argtypes = [ctypes.POINTER(c_string),private_key,ctypes.POINTER(c_string)]
	lib.print_hex.restype = None
	lib.print_hex.argtypes = [int1024,ctypes.POINTER(c_string)]
	lib.read_hex.restype = int1024
	lib.read_hex.argtypes = [ctypes.POINTER(c_string)]
	lib.print_c_string.restype = None
	lib.print_c_string.argtypes = [ctypes.POINTER(c_string)]
	lib.read_c_string.restype = None
	lib.read_c_string.argtypes = [ctypes.POINTER(c_string)]

	
	
	return lib
	
#najdluzszy_palindrom.c
def palindrom_init():
	nazwa = 'najdluzszy_palindrom'

	if os.name == 'posix':
		compile_command = [
			"gcc",
			"-shared",
			"-fPIC",
			nazwa+'.c',
			"-o",
			nazwa+'.so'
			]
		try:
			subprocess.run(compile_command, check=True)
		except:
			print("Cos poszlo zle :( Upewnij sie ze masz zainstalowane gcc")
			exit()
		lib = ctypes.CDLL("./"+nazwa+".so")
	elif os.name == 'nt':
			try:
					os.environ['PATH'] = r'C:\msys64\mingw64\bin;' + os.environ['PATH']
					subprocess.run(['gcc', '-shared', nazwa+'.c', '-o', nazwa + '.dll'], check=True)
			except:
					print("Cos poszlo zle :( Upewnij sie ze masz zainstalowane gcc")
					exit()
			lib = ctypes.CDLL('./'+nazwa+'.dll')
	#kod z konwerter.py
	lib.find_longest_palindrome.restype = ctypes.c_char_p
	lib.find_longest_palindrome.argtypes = [ctypes.c_char_p]

	
	return lib




#plot.c
def plot_init():

	nazwa = 'plot'

	if os.name == 'posix':
		compile_command = [
			"gcc",
			"-shared",
			"-fPIC",
			nazwa+'.c',
			"-o",
			nazwa+'.so'
			]
		try:
			subprocess.run(compile_command, check=True)
		except:
			print("Cos poszlo zle :( ")
			exit()
		lib = ctypes.CDLL("./"+nazwa+".so")
	elif os.name == 'nt':
			try:
					os.environ['PATH'] = r'C:\msys64\mingw64\bin;' + os.environ['PATH']
					subprocess.run(['gcc', '-shared', nazwa+'.c', '-o', nazwa + '.dll'], check=True)
			except:
					print("Cos poszlo zle :( ")
					exit()
			lib = ctypes.CDLL('./'+nazwa+'.dll')
	#kod z konwerter.py


	lib.readString.restype = ctypes.c_char_p
	lib.readString.argtypes = []
	lib.szyfruj.restype = None
	lib.szyfruj.argtypes = []
	return lib

#nawiasowanie.c
def nawiasowanie_init():
	nazwa = 'nawiasowanie'

	if os.name == 'posix':
		compile_command = [
			"gcc",
			"-shared",
			"-fPIC",
			nazwa+'.c',
			"-o",
			nazwa+'.so'
			]
		try:
			subprocess.run(compile_command, check=True)
		except:
			print("Cos poszlo zle :( Upewnij sie ze masz zainstalowane gcc")
			exit()
		lib = ctypes.CDLL("./"+nazwa+".so")
	elif os.name == 'nt':
			try:
					os.environ['PATH'] = r'C:\msys64\mingw64\bin;' + os.environ['PATH']
					subprocess.run(['gcc', '-shared', nazwa+'.c', '-o', nazwa + '.dll'], check=True)
			except:
					print("Cos poszlo zle :( Upewnij sie ze masz zainstalowane gcc")
					exit()
			lib = ctypes.CDLL('./'+nazwa+'.dll')
	#kod z konwerter.py

	lib.removecomments.restype = None
	lib.removecomments.argtypes = [ctypes.c_char_p,ctypes.c_char]
	lib.check.restype = ctypes.c_int
	lib.check.argtypes = [ctypes.c_char_p]


	
	return lib

#regex.c

def regex_init():
	nazwa = 'regex'

	if os.name == 'posix':
		compile_command = [
			"gcc",
			"-shared",
			"-fPIC",
			nazwa+'.c',
			"-o",
			nazwa+'.so'
			]
		try:
			subprocess.run(compile_command, check=True)
		except:
			print("Cos poszlo zle :( Upewnij sie ze masz zainstalowane gcc")
			exit()
		lib = ctypes.CDLL("./"+nazwa+".so")
	elif os.name == 'nt':
			try:
					os.environ['PATH'] = r'C:\msys64\mingw64\bin;' + os.environ['PATH']
					subprocess.run(['gcc', '-shared', nazwa+'.c', '-o', nazwa + '.dll'], check=True)
			except:
					print("Cos poszlo zle :( Upewnij sie ze masz zainstalowane gcc")
					exit()
			lib = ctypes.CDLL('./'+nazwa+'.dll')
	#kod z konwerter.py
	lib.match.restype = ctypes.c_int
	lib.match.argtypes = [ctypes.c_char_p,ctypes.c_char_p]
	lib.reg_ast.restype = ctypes.c_int
	lib.reg_ast.argtypes = [ctypes.c_char,ctypes.c_char_p,ctypes.c_char_p]
	lib.reg_pl.restype = ctypes.c_int
	lib.reg_pl.argtypes = [ctypes.c_char,ctypes.c_char_p,ctypes.c_char_p]
	lib.reg_br.restype = ctypes.c_int
	lib.reg_br.argtypes = [ctypes.c_char,ctypes.c_int,ctypes.c_int,ctypes.c_char_p,ctypes.c_char_p]
	lib.parse_dgt.restype = ctypes.c_int
	lib.parse_dgt.argtypes = [ctypes.POINTER(ctypes.c_char_p)]
	#lib.reverse.restype = None
	#lib.reverse.argtypes = [ctypes.c_char_p]
	#lib.int_str.restype = None
	#lib.int_str.argtypes = [ctypes.c_int,ctypes.c_char_p]
	#lib.match_pos.restype = ctypes.c_int
	#lib.match_pos.argtypes = [ctypes.c_char_p,ctypes.c_char_p]
	return lib

#regex.c

def rozpoznawanie_jezyka_init():
	nazwa = 'rozpoznawanie_jezyka'

	if os.name == 'posix':
		compile_command = [
			"gcc",
			"-shared",
			"-fPIC",
			nazwa+'.c',
			'biblioteka.c',
			"-o",
			nazwa+'.so'
			]
		try:
			subprocess.run(compile_command, check=True)
		except:
			print("Cos poszlo zle :( Upewnij sie ze masz zainstalowane gcc")
			exit()
		lib = ctypes.CDLL("./"+nazwa+".so")
	elif os.name == 'nt':
			try:
					os.environ['PATH'] = r'C:\msys64\mingw64\bin;' + os.environ['PATH']
					subprocess.run(['gcc', '-shared', nazwa+'.c', 'biblioteka.c','-o',  nazwa + '.dll'], check=True)
			except:
					print("Cos poszlo zle :( Upewnij sie ze masz zainstalowane gcc")
					exit()
			lib = ctypes.CDLL('./'+nazwa+'.dll')
	#kod z konwerter.py
	lib.detect_language.restype = ctypes.c_char_p
	lib.detect_language.argtypes = [ctypes.c_char_p]
	
	return lib
	
def biblioteka_init():
	nazwa = 'biblioteka'

	if os.name == 'posix':
		compile_command = [
			"gcc",
			"-shared",
			"-fPIC",
			nazwa+'.c',
			"-o",
			nazwa+'.so'
			]
		try:
			subprocess.run(compile_command, check=True)
		except:
			print("Cos poszlo zle :( Upewnij sie ze masz zainstalowane gcc")
			exit()
		lib = ctypes.CDLL("./"+nazwa+".so")
	elif os.name == 'nt':
			try:
					os.environ['PATH'] = r'C:\msys64\mingw64\bin;' + os.environ['PATH']
					subprocess.run(['gcc', '-shared', nazwa+'.c', '-o',  nazwa + '.dll'], check=True)
			except:
					print("Cos poszlo zle :( Upewnij sie ze masz zainstalowane gcc")
					exit()
			lib = ctypes.CDLL('./'+nazwa+'.dll')
	#kod z konwerter.py

	lib.statystyki.restype = None
	lib.statystyki.argtypes = [ctypes.c_char_p,ctypes.POINTER(TextStats)]
	lib.wyszukiwanie_wzorca.restype = None
	lib.wyszukiwanie_wzorca.argtypes = [ctypes.c_char_p,ctypes.c_char_p]
	lib.wyszukiwanie_znaku_specjalnego.restype = None
	lib.wyszukiwanie_znaku_specjalnego.argtypes = [ctypes.c_char_p,ctypes.c_char_p]
	lib.ignorowanie_wielkosci_liter.restype = None
	lib.ignorowanie_wielkosci_liter.argtypes = [ctypes.c_char_p,ctypes.c_char_p]
	lib.wypisz_tekst_wersja1.restype = None
	lib.wypisz_tekst_wersja1.argtypes = [ctypes.c_char_p,ctypes.c_int,ctypes.c_int]
	lib.wypisz_tekst_wersja2.restype = None
	lib.wypisz_tekst_wersja2.argtypes = [ctypes.c_char_p,ctypes.c_int,ctypes.c_int]
	lib.wypisanie_statystyk_liter.restype = None
	lib.wypisanie_statystyk_liter.argtypes = [TextStats]
	lib.zliczanie_wzorca.restype = ctypes.c_int
	lib.zliczanie_wzorca.argtypes = [ctypes.c_char_p,ctypes.c_char_p]
	lib.podmiana_wzorca.restype = None
	lib.podmiana_wzorca.argtypes = [ctypes.c_char_p,ctypes.c_char_p,ctypes.c_char_p,ctypes.c_char_p]


	
	return lib
	
def podzial_init():
	nazwa = 'podzial'

	if os.name == 'posix':
		compile_command = [
			"gcc",
			"-shared",
			"-fPIC",
			nazwa+'.c',
			"-o",
			nazwa+'.so'
			]
		try:
			subprocess.run(compile_command, check=True)
		except:
			print("Cos poszlo zle :( Upewnij sie ze masz zainstalowane gcc")
			exit()
		lib = ctypes.CDLL("./"+nazwa+".so")
	elif os.name == 'nt':
			try:
					os.environ['PATH'] = r'C:\msys64\mingw64\bin;' + os.environ['PATH']
					subprocess.run(['gcc', '-shared', nazwa+'.c', '-o',  nazwa + '.dll'], check=True)
			except:
					print("Cos poszlo zle :( Upewnij sie ze masz zainstalowane gcc")
					exit()
			lib = ctypes.CDLL('./'+nazwa+'.dll')
	#kod z konwerter.py

	lib.zwolnij.restype = None
	lib.zwolnij.argtypes = [ctypes.POINTER(ctypes.c_char_p),ctypes.c_int]
	lib.porownaj_slowo.restype = ctypes.c_int
	lib.porownaj_slowo.argtypes = [ctypes.c_void_p,ctypes.c_void_p]
	lib.wczytaj_slownik.restype = ctypes.POINTER(ctypes.c_char_p)
	lib.wczytaj_slownik.argtypes = [ctypes.c_char_p,ctypes.POINTER(ctypes.c_int)]
	lib.najlepszy_podzial.restype = ctypes.c_int
	lib.najlepszy_podzial.argtypes = [ctypes.c_char_p,ctypes.POINTER(ctypes.c_char_p),ctypes.c_int,ctypes.POINTER(ctypes.POINTER(ctypes.c_char_p)),ctypes.POINTER(ctypes.c_int),ctypes.POINTER(ctypes.POINTER(ctypes.c_char_p)),ctypes.POINTER(ctypes.c_int)]
	lib.podziel_na_zdania.restype = ctypes.POINTER(ctypes.c_char_p)
	lib.podziel_na_zdania.argtypes = [ctypes.c_char_p,ctypes.POINTER(ctypes.c_int)]
	lib.polacz_wyniki_do_ciagu.restype = None
	lib.polacz_wyniki_do_ciagu.argtypes = [ctypes.POINTER(ctypes.c_char_p),ctypes.c_int,ctypes.POINTER(ctypes.c_char_p),ctypes.POINTER(ctypes.c_char_p),ctypes.c_int]
	lib.sprawdz_gramatyke.restype = None
	lib.sprawdz_gramatyke.argtypes = [ctypes.c_char_p]



	
	return lib
	
def arithmetic_init():
	nazwa = 'arithmetic'

	if os.name == 'posix':
		compile_command = [
			"g++",
			'-std=c++17',
			"-shared",
			"-fPIC",
			nazwa+'.cpp',
			"-o",
			nazwa+'.so'
			]
		try:
			subprocess.run(compile_command, check=True)
		except:
			print("Cos poszlo zle :( Upewnij sie ze masz zainstalowane gcc")
			exit()
		lib = ctypes.CDLL("./"+nazwa+".so")
	elif os.name == 'nt':
			try:
					os.environ['PATH'] = r'C:\msys64\mingw64\bin;' + os.environ['PATH']
					subprocess.run(['g++', '-std=c++17',"-static",'-shared', nazwa+'.cpp', '-o',  nazwa + '.dll'], check=True)
			except:
					print("Cos poszlo zle :( Upewnij sie ze masz zainstalowane gcc")
					exit()
			lib = ctypes.CDLL('./'+nazwa+'.dll')
	#kod z konwerter.py

	lib.c_compress.restype = None
	lib.c_compress.argtypes = [ctypes.c_char_p,ctypes.c_char_p]
	lib.c_decompress.restype = None
	lib.c_compress.argtypes = [ctypes.c_char_p,ctypes.c_char_p]



	
	return lib

def base64_init():
	nazwa = 'base64'

	if os.name == 'posix':
		compile_command = [
			"g++",
			'-std=c++17',
			"-shared",
			"-fPIC",
			nazwa+'.cpp',
			"-o",
			nazwa+'.so'
			]
		try:
			subprocess.run(compile_command, check=True)
		except:
			print("Cos poszlo zle :( Upewnij sie ze masz zainstalowane g++")
			exit()
		lib = ctypes.CDLL("./"+nazwa+".so")
	elif os.name == 'nt':
			try:
					os.environ['PATH'] = r'C:\msys64\mingw64\bin;' + os.environ['PATH']
					subprocess.run(['g++', '-std=c++17','-shared',"-static", nazwa+'.cpp', '-o',  nazwa + '.dll'], check=True)
			except:
					print("Cos poszlo zle :( Upewnij sie ze masz zainstalowane g++")
					exit()
			lib = ctypes.CDLL('./'+nazwa+'.dll')
	#kod z konwerter.py
	lib.c_encode1421.restype = ctypes.c_char_p
	lib.c_encode1421.argtypes = [ctypes.c_char_p]
	lib.c_encode2045.restype = ctypes.c_char_p
	lib.c_encode2045.argtypes = [ctypes.c_char_p]
	lib.c_encode2152.restype = ctypes.c_char_p
	lib.c_encode2152.argtypes = [ctypes.c_char_p]
	lib.c_encode3501.restype = ctypes.c_char_p
	lib.c_encode3501.argtypes = [ctypes.c_char_p]
	lib.c_encode4648_4.restype = ctypes.c_char_p
	lib.c_encode4648_4.argtypes = [ctypes.c_char_p]
	lib.c_encode4648_5.restype = ctypes.c_char_p
	lib.c_encode4648_5.argtypes = [ctypes.c_char_p]
	lib.c_encode4880.restype = ctypes.c_char_p
	lib.c_encode4880.argtypes = [ctypes.c_char_p]
	lib.c_decode1421.restype = ctypes.c_char_p
	lib.c_decode1421.argtypes = [ctypes.c_char_p]
	lib.c_decode2045.restype = ctypes.c_char_p
	lib.c_decode2045.argtypes = [ctypes.c_char_p]
	lib.c_decode2152.restype = ctypes.c_char_p
	lib.c_decode2152.argtypes = [ctypes.c_char_p]
	lib.c_decode3501.restype = ctypes.c_char_p
	lib.c_decode3501.argtypes = [ctypes.c_char_p]
	lib.c_decode4648_4.restype = ctypes.c_char_p
	lib.c_decode4648_4.argtypes = [ctypes.c_char_p]
	lib.c_decode4648_5.restype = ctypes.c_char_p
	lib.c_decode4648_5.argtypes = [ctypes.c_char_p]
	lib.c_decode4880.restype = ctypes.c_char_p
	lib.c_decode4880.argtypes = [ctypes.c_char_p]



	
	return lib




def get_all_libs():
	lib = {}
	lib['biblioteka'] = biblioteka_init()
	lib['palindrom'] = palindrom_init()
	lib['szyfr_rsa'] = szyfr_rsa_init()
	lib['plot'] = plot_init()
	lib['podzial'] = podzial_init()
	lib['regex'] = regex_init()
	lib['rozpoznawanie_jezyka'] = rozpoznawanie_jezyka_init()
	lib['nawiasowanie'] = nawiasowanie_init()
	lib['arithmetic'] = arithmetic_init()
	lib['base64'] = base64_init()
	return lib
