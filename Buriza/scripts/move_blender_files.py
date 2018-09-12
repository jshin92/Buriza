import argparse
from os import listdir
from os.path import isfile,join
from shutil import copyfile

omitted_extensions = ['blend', 'blend1']

def extension(filename):
    return filename.split('.')[1]

def move_files(src_root, asset_folder, dest):
    full_path = join(src_root, asset_folder)
    files = [f for f in listdir(full_path) if extension(f) not in omitted_extensions]
    for file in files:
        src_path = join(src_root, asset_folder, file)
        dest_path = join(dest, asset_folder)
        print(src_path)
        print(dest_path)

def main():
    parser = argparse.ArgumentParser(description='Moves blender assets from target to source.')
    parser.add_argument('--src-root', required=True)
    parser.add_argument('--asset-folder', required=True)
    parser.add_argument('--dest', required=True)
    args = parser.parse_args()

    src_root = args.src_root
    asset_folder = args.asset_folder
    dest = args.dest
    move_files(src_root, asset_folder, dest)

if __name__ == '__main__':
    main()
