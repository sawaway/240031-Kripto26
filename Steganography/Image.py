from PIL import Image

img = Image.open("gambar2.jpeg").convert("RGB")
with open("gambar2.ppm", "w") as f:
    f.write(f"P3\n{img.width} {img.height}\n255\n")
    f.write(" ".join(f"{r} {g} {b}" for r, g, b in img.getdata()))

print("Berhasil mengubah ke PPM P3!")