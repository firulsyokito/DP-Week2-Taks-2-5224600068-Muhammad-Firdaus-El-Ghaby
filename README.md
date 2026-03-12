# Refleksi

### 1. What is the invariant structure of your game?

Struktur invariant adalah **urutan fase** di `RunSession::run()` yang tidak boleh diubah: Generate Hand → Choose Hand → Compute Score → Check Win/Lose → Count Cash → Shop → Advance Round. `RunSession` hanya bertugas menjaga urutan ini — ia tidak menyimpan logika scoring, reward, maupun input generation. Tugasnya murni mengatur alur, bukan menentukan perilaku.

### 2. What parts are mutable?

Semua perilaku yang diinjeksikan ke `RunSession` lewat konstruktor: `IHandGenerator` (cara deck dibuat), `IHandChooser` (cara kartu dipilih), `ScoringPipeline` (cara chips & mult dihitung), `IRewardRule` (cara uang dihitung), dan `ShopSystem` (item yang ditawarkan). Semua ini bisa diganti bebas tanpa menyentuh `RunSession`.

### 3. If you wanted to add a new feature, which class would change?

Karena `RunSession` bergantung pada abstraksi `IHandGenerator`, bukan class konkretnya. Ia hanya memanggil `generateDeck()` dan menerima kartu — tidak peduli apakah kartu itu urutan tetap atau acak. Penggantian dari `SequentialInputGenerator` ke `RandomInputGenerator` cukup dilakukan di `main.cpp`. Kontraknya tidak berubah, sehingga `RunSession` tidak perlu dimodifikasi sama sekali.

### 4. If you changed the loop order, what would break?

`RunSession` harus diedit setiap kali scoring berubah — artinya invariant ikut disentuh hanya karena bagian mutable dimodifikasi. Urutan fase dan formula scoring akan tercampur dalam satu class, membuat keduanya saling bergantung dan rapuh. Sistem juga tidak bisa berkembang: setiap aturan baru harus ditambah langsung ke `RunSession` hingga class tersebut tidak lagi bisa dikelola.
