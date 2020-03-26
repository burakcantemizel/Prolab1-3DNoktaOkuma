<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
<HEAD>
	<META HTTP-EQUIV="CONTENT-TYPE" CONTENT="text/html; charset=utf-8">
	<META NAME="GENERATOR" CONTENT="LibreOffice 4.1.6.2 (Linux)">
	<META NAME="AUTHOR" CONTENT="IEEE">
	<META NAME="CREATED" CONTENT="20180818;231400000000000">
	<META NAME="CHANGEDBY" CONTENT="Burak Can TEMİZEL">
	<META NAME="CHANGED" CONTENT="20191026;231500000000000">
	<META NAME="__Grammarly_42___1" CONTENT="H4sIAAAAAAAEAKtWcslP9kxRslIyNDYyNDU0N7QwMTMwNjY3NzZT0lEKTi0uzszPAykwrAUAt9LCuywAAAA=">
	<META NAME="__Grammarly_42____i" CONTENT="H4sIAAAAAAAEAKtWckksSQxILCpxzi/NK1GyMqwFAAEhoTITAAAA">


</HEAD>
<BODY LANG="en-US" TEXT="#000000" LINK="#0000ff" DIR="LTR">
<H1 ALIGN=CENTER STYLE="text-indent: 0in; margin-top: 0.07in; margin-bottom: 0.07in; line-height: 100%">
	<FONT SIZE=12>Programlama Laboratuvarı Raporu</FONT></H1>
<H2 ALIGN=CENTER STYLE="text-indent: 0in; margin-top: 0.07in; margin-bottom: 0.07in; line-height: 100%">
<FONT SIZE=16>3D Nokta Okuma</FONT></H2>

<P ALIGN=CENTER STYLE="text-indent: 0in; margin-top: 0.07in; margin-bottom: 0.07in; line-height: 50%">
<BR><BR>
</P>
<DIV ID="Section1" DIR="LTR" GUTTER=48 STYLE="column-count: 3">
	<P ALIGN=CENTER STYLE="text-indent: 0in; margin-top: 0.07in; margin-bottom: 0.03in; line-height: 100%">
	<FONT SIZE=2 STYLE="font-size: 11pt"><FONT SIZE=3>Özge POYRAZ
	<BR>Kocaeli Üniversitesi</FONT><FONT SIZE=3><I> <BR></I></FONT><FONT SIZE=3>Mühendislik
	Fakültesi</FONT><FONT SIZE=3><BR>Bilgisayar Mühendisliği</FONT><FONT SIZE=3><I>
	<BR></I></FONT><FONT SIZE=3>180202025@kocaeli.edu.tr</FONT></FONT></P>
	<P ALIGN=CENTER STYLE="text-indent: 0in; margin-top: 0.07in; margin-bottom: 0.03in; line-height: 100%">
	<BR><BR>
	</P>
	<P ALIGN=CENTER STYLE="text-indent: 0in; margin-top: 0.07in; margin-bottom: 0.03in; line-height: 100%">
	 <FONT SIZE=2 STYLE="font-size: 11pt"><FONT SIZE=3>Burak Can
	TEMİZEL<BR>Kocaeli Üniversitesi</FONT><FONT SIZE=3><I><BR></I></FONT><FONT SIZE=3>Mühendislik
	Fakültesi</FONT><FONT SIZE=3><BR>Bilgisayar Mühendisliği</FONT><FONT SIZE=3><I>
	<BR></I></FONT><FONT SIZE=3>180202024@kocaeli.edu.tr</FONT></FONT></P>
</DIV>
<DIV ID="Section2" DIR="LTR" GUTTER=48 STYLE="column-count: 3">
	<P CLASS="western" ALIGN=CENTER STYLE="text-indent: 0in; margin-bottom: 0in; line-height: 100%">
	<BR>
	</P>
</DIV>
<DIV ID="Section3" DIR="LTR" GUTTER=24 STYLE="column-count: 2">
	<P STYLE="text-indent: 0.19in; line-height: 100%"><FONT SIZE=2 STYLE="font-size: 9pt"><I><B><FONT COLOR="#000000"><FONT SIZE=3 STYLE="font-size: 13pt">Özet—Bu
	çalışmada genel olarak 3 boyutlu uzayda belirli nokta kümeleriyle
	geometrik işlemler gerçekleştirdik ve bu işlemlerden birtakım
	sonuçlar elde ettik. Bu işlemleri gerçekleştirirken nokta
	bilgilerini dosya girdileri olarak aldık bu da bize fazla sayıda
	veri ile işlem yapma imkanı sağladı. Bu şekilde program büyük
	veri dosyalarını işleyerek işlemlerin çok hızlı bir şekilde
	yapılıp sonuçların elde edilmesini oldukça kolaylaştırdı.
	Veri dosyalarıyla yapılan bu işlemler aynı zamanda bize
	verilerin görselleştirilmesi ve incelenmesi fırsatını da verdi.
	İşlemleri gerçekleştiren yapıyı kurduktan sonra ayrı bir
	programda verilerimizi görselleştirerek sonuçların doğruluğunu
	test etmiş olduk. Program yapısal olarak dosya okuma, geometrik
	işlemleri gerçekleştirme ve sonuç verme aşamalarından
	oluşuyor. Dosya okurken farklı veri tipinde dosyaların okuması
	gerçekleştiriliyor ve nokta bilgileri elde ediliyor. Daha sonra bu
	nokta bilgileri kullanılarak çeşitli işlemler gerçekleştiriliyor
	ve aynı veri tipinde hesaplanan yeni nokta bilgilerini kullanıcıya
	çıktı olarak veriyor. Bu proje dosya işlemleri, dinamik bellek
	kullanımı, lineer cebir ve geometrik işlemler gibi konularda çok
	sayıda kazanım elde etmemizi sağladı.</FONT></FONT></B></I></FONT></P>
	<H1 LANG="en-US" CLASS="western">I.<FONT SIZE=3><B>PROJE HAKKINDA</B></FONT></H1>
	<P LANG="en-US" CLASS="western"><FONT SIZE=3><SPAN LANG="tr-TR">Gerçekleştirdiğimiz
	proje birkaç temel aşamadan oluşmaktaydı ve her aşamanın
	kendine göre isterleri bulunmaktaydı. Proje kaba olarak özel bir
	dosya formatından okuduğumuz nokta verilerini belli işlemlerden
	geçirip kullanıcıya bir çıktı vermek üzerineydi. Daha
	ayrıntılı olarak bahsetmemiz gerekirse “.nkt” uzantılı
	olarak hazırlanmış yazı belgelerinde bir dosya yapısı
	oluşturulmuş ve içerisine farklı veri tiplerinde ve farklı
	parametreler içeren nokta bilgileri yazılmıştı. Programımızla
	bu dosyalardan noktaları okuyup işleme başlamadan önce ayrıca
	gerçekleştirmemiz gereken ek dosya işlemleri mevcuttu. Burada en
	önemli hususlardan birisi bir klasörden bilinmeyen sayıda
	dosyanın otomatik bir şekilde okunmasıydı. Bu konuya daha sonra
	yöntemler ve program mimarisi kısmında detaylıca değinilecektir.
	Dinamik bir dosya okuma yapısı kurulduktan sonra noktalar okunacak
	ve istediğimiz işlemleri gerçekleştirebilmek için belleğe
	atılacaktı. Daha sonra elde ettiğimiz verilerle hedeflediğimiz
	sonuçları elde etmek için kullanmamız gereken matematiksel
	yöntemleri hazırlamamız gerekecekti. Yine aynı şekilde bu
	işlemlerin matematiksel modellemelerine raporun ileri kısımlarında
	değinilecektir.</SPAN></FONT><FONT COLOR="#000000"><FONT SIZE=3>
	Bazı matematiksel işlemler az sayıda veri ile hızlı ve kolay
	bir şekilde gerçekleştirilebilir.&nbsp; Çok sayıda verinin
	işlenmesi, hesaplanması çok fazla zaman ve emek ister. Bu
	problemleri çözmek amacıyla hazırlanmış bilgisayar
	programlarından yardım almak; zamanı oldukça azaltacaktır, efor
	kaybına engel olacaktır ve hata payını ortadan kaldıracaktır.
	Bu programı hazırlarken sürekli büyük verilerle
	kullanabileceğini düşünerek ona göre bir mimari hazırlamaya
	özen gösterdik. Hem yavaş çalışmaması hem de kaynakları iyi
	kullanması gerekiyordu. Bu amacı gerçekleştirmek için çeşitli
	yöntemler izledik. Dosya işlemlerini gerçekleştirdikten sonra
	elde ettiğimiz no</FONT></FONT><FONT COLOR="#000000"><FONT SIZE=3><SPAN LANG="tr-TR">kta</SPAN></FONT></FONT><FONT COLOR="#000000"><FONT SIZE=3>
	verileriyle matematiksel işlemleri gerçekleştirdik. Programımızın
	temel amaçlarından</FONT></FONT><FONT COLOR="#000000"><FONT SIZE=3><SPAN LANG="tr-TR">
	birisi</SPAN></FONT></FONT><FONT COLOR="#000000"><FONT SIZE=3>
	dosyalardan alınan verileri</FONT></FONT><FONT COLOR="#000000"><FONT SIZE=3><SPAN LANG="tr-TR">
	okuyup işlemleri gerçekleştirip noktaları uzun süreli bellekte
	tutmaktan kaçınmaktı</SPAN></FONT></FONT><FONT COLOR="#000000"><FONT SIZE=3>.</FONT></FONT><FONT COLOR="#000000"><FONT SIZE=3><SPAN LANG="tr-TR">
	Daha sonra elde edilen sonuçları kullanıcıya tekrar bir dosya
	olarak sunmamız gerekiyordu. Burada işlemden geçirdiğimiz nokta
	verilerinin sonuçlarını bir sınıflandırmaya tabi tutup
	okuduğumuz veri tipinde çıktı işlemini gerçekleştirdik.
	Binary ve ascii dosyalar için farklı çıktılar oluşturduk.</SPAN></FONT></FONT></P>
	<H1 LANG="en-US" CLASS="western">II.<FONT SIZE=3><B>YÖNTEMLER VE
	PROGRAM MİMARİSİ</B></FONT></H1>
	<H2 LANG="en-US" CLASS="western"><FONT SIZE=3><B>A.Dosya İşlemleri</B></FONT></H2>
	<P LANG="en-US" CLASS="western"><FONT SIZE=3><SPAN LANG="tr-TR">Programımız
	çok sayıda dosya işlemini gerçekleştiren bir yapıdaydı.
	Burada ilk ve önemli bir husus olarak karşımıza dinamik dosya
	okuması çıkmaktaydı. Verilen istere göre programımız otomatik
	olarak klasöründe bulunan “.nkt” dosyalarını işleme
	sokmalıydı. Bunun için sadece dosya işlemleri yetmemekteydi aynı
	zamanda klasör işlemleri gerçekleştirmeliydik. Klasör bilgisini
	edinmek için Open Group Library “dirent.h” kütüphanesini
	kullandık. Bu başlık dosyası içerdiği özel değişken
	tipleri, veri yapıları ve fonksiyonlarla klasör işlemlerini
	gerçekleştirmemizi sağladı. Burada temel olarak kullandığımız
	fonksiyon ve yapılardan bazıları klasörü açmak için
	opendir(), klasör okuma işlemi için readdir(), klasör kaynağı
	tipi olan DIR ve girdilere ulaşmak için dirent struct yapısıydı.</SPAN></FONT><FONT SIZE=3>
	</FONT><FONT SIZE=3><SPAN LANG="tr-TR">Bu ve bunun gibi yapılarla
	dosya girdilerimize ulaşıp istediğimiz şekilde dosya
	dizilerimizi yaratarak gerekli ortamı oluşturmuş olduk. Daha
	sonrasında da dosya işlemlerimizi gerçekleştirdik</SPAN></FONT><SPAN LANG="tr-TR">.
	</SPAN><FONT SIZE=3><SPAN LANG="tr-TR">Dosya işlemlerimizi
	gerçekleştirirken kullanıcıdan aldığımız dosyanın veri
	tipine göre binary okuma ve yazma işlemi de gerçekleştirdik.
	Binary işlemlerini gerçekleştirirken değerlerimizin doğruluğunu
	çeşitli hex editörler ile test ettik.</SPAN></FONT></P>
	<H2 LANG="en-US" CLASS="western"><FONT SIZE=3><B>B.Verilerin
	Okunması ve Saklanması</B></FONT></H2>
	<P LANG="en-US" CLASS="bullet-list-western" STYLE="margin-left: 0in; text-indent: 0in">
		<FONT SIZE=3><SPAN LANG="tr-TR">Programımızın bellekte daha az
	alan tüketmesi için okuduğumuz verileri tek bir dinamik struct
	dizisinde tutmaya çalıştık böylece her dosya için sürekli
	aynı diziyi tekrar tekrar boyutlandırarak işleme sokup bu şekilde
	noktaları depoladık. Daha sonra bu diziyi işlemlere göndererek
	kullandık. Dosyalardan hataları yakalarken tüm dosya yapısını
	halihazırda okumuş olacağımız için buradan elde ettiğimiz
	dosya verilerini yine sadece dosyalarla ilgili bilgilerin saklanması
	ve hataların tutulması amacıyla oluşturduğumuz dinamik struct
	dizilerinde sakladık bu da daha sonra program akışında veri
	tipleri, parametre tipleri ve dosyalarla ilgili bilgileri
	yönlendirirken oldukça işimize yaradı ve tekrar tekrar
	dosyalardan bilgi okuma zorunluluğumuzu ortadan kaldırdı.</SPAN></FONT></P>
	<H2 LANG="en-US" CLASS="western"><FONT SIZE=3><B>C.Matematiksel
	İşlemler</B></FONT></H2>
	<P LANG="en-US" CLASS="western"><FONT SIZE=3><SPAN LANG="tr-TR">Dosyalardan
	elde ettiğimiz verileri farklı işlemlerden geçirip bazı
	çıktılar elde etmemiz gerekiyordu. Burada her işlem için farklı
	matematiksel metotlar kullandık. En yakın ve en uzak probleminde
	iki nokta arasındaki uzaklığı Pisagor teoreminden faydalanarak
	tespit ederek işlemlerimizi gerçekleştirdik. En küçük küp
	problemine geldiğimizde yine aynı teoremden faydalanarak her eksen
	için noktalar kümesinde maksimum uzunluğu bularak küpün sahip
	olacağı ayrıtı tespit ettik. Daha sonrasında yine her eksendeki
	uzaklık farkından faydalanarak küpün merkez noktasını bulduk
	ve ayrıt uzunluğundan da faydalanarak köşe koordinatlarını
	oluşturduk. Bu sırada fark ettik ki eğer herhangi bir eksende
	maksimum uzaklık diğer bir eksenden küçükse yani küpün her
	kenarına bir nokta temas etmiyorsa aslında hacmi sabit kalmakla
	birlikte sonsuz pozisyonda küp tüm noktaları içine alabilecekti.
	Programımız yapısal olarak bir konsol uygulaması olduğu için
	bunu görselleştirme imkanımız yoktu. Daha sonra Processing
	Java’da ayrı bir program yazarak işlemlerimizin matematiksel
	modellerini görselleştirdik. Böylece kendi programımızdaki
	sonuçlarımızın doğruluğunu teyit etmiş olduk.      </SPAN></FONT>
	</P>
	<P LANG="tr-TR" CLASS="western" STYLE="text-indent: 0in"><IMG SRC="http://burakcantemizel.com/resimler/3dn2.png" NAME="graphics1" ALIGN=BOTTOM  BORDER=0></P>
	<P LANG="tr-TR" CLASS="western" STYLE="text-indent: 0in"><IMG SRC="http://burakcantemizel.com/resimler/3dn4.png" NAME="graphics2" ALIGN=BOTTOM  BORDER=0></P>
	<P ALIGN=CENTER STYLE="text-indent: 0in; margin-top: 0.17in; margin-bottom: 0.17in; line-height: 90%">
	<FONT FACE="Symbol, serif"><FONT FACE="Times New Roman, serif"><FONT SIZE=2 STYLE="font-size: 11pt"><I>Kullandığımız
	matematiksel modellemelerin görselleştirilmesi</I></FONT></FONT></FONT></P>
	<H2 LANG="en-US" CLASS="western"><FONT SIZE=3><B>D.Program Çıktıları</B></FONT></H2>
	<P LANG="en-US" CLASS="bullet-list-western" STYLE="margin-left: 0in; text-indent: 0in">
	<SPAN LANG="tr-TR">	</SPAN><FONT SIZE=3><SPAN LANG="tr-TR">Programımız
	farklı veri tiplerinde dosyalarla işlem yaptığı için
	çıktılarımızı da buna göre biçimlendirmek zorundaydık.
	Binary dosya çıktılarını oluştururken öncelikle verilerimizin
	binarye doğru bir şekilde dönüştürüldüğünü test ettik ve
	daha öncesinde program akışını kontrol etmek için
	hazırladığımız çeşitli yapılarla bu verileri çıktı olarak
	kullanıcıya sunduk.</SPAN></FONT></P>
	<H2 LANG="en-US" CLASS="western">E.<FONT SIZE=3><SPAN LANG="tr-TR"><B>Programın
	Genel Yapısı ve Tasarım</B></SPAN></FONT></H2>
	<P CLASS="western" ALIGN=JUSTIFY STYLE="margin-bottom: 0in; line-height: 100%">
	<FONT SIZE=3><SPAN LANG="tr-TR">Programın genel yapısı ve işleyiş
	algoritması raporun en sonunda verilmiştir. Tasarım olarak
	standart bir konsol uygulaması biçimindedir</SPAN></FONT><SPAN LANG="tr-TR">.</SPAN></P>
	<P LANG="tr-TR" CLASS="western" ALIGN=JUSTIFY STYLE="margin-bottom: 0in; line-height: 100%">
	<BR>
	</P>
	<P LANG="tr-TR" CLASS="western" ALIGN=JUSTIFY STYLE="text-indent: 0in; margin-bottom: 0in; line-height: 100%">
	<IMG SRC="http://burakcantemizel.com/resimler/3dn1.png" NAME="graphics3" ALIGN=BOTTOM  BORDER=0></P>
	<P LANG="tr-TR" CLASS="western" ALIGN=CENTER STYLE="text-indent: 0in; margin-bottom: 0in; line-height: 100%">
	<BR>
	</P>
	<P LANG="tr-TR" CLASS="western" ALIGN=CENTER STYLE="text-indent: 0in; margin-bottom: 0in; line-height: 100%">
	<I>Programın Genel Arayüzü</I></P>
	<P LANG="tr-TR" CLASS="western" ALIGN=CENTER STYLE="text-indent: 0in; margin-bottom: 0in; line-height: 100%">
	<BR>
	</P>
	<H2 LANG="tr-TR" CLASS="western"><FONT SIZE=3><B>F.Performans</B></FONT></H2>
	<P CLASS="western" ALIGN=JUSTIFY STYLE="margin-bottom: 0in; line-height: 100%">
	<FONT COLOR="#c00000"><FONT SIZE=3><SPAN LANG="tr-TR">Program çok
	sayıda veriyle işlem gerçekleştirebileceği için derlenirken
	optimize edilmesi performansını büyük ölçüde etkilemektedir.
	Codeblocks Mingw derleyicisinin içindeki gcc.exe ile yapılan
	derleme işleminde      -O2 veya -O3 optimizasyon parametreleriyle
	yapılan derleme işlemlerinde çok büyük bir hız farkı
	oluşmaktadır ve direkt olarak derlenebilmektedir. Eğer bu
	optimizasyonlar gerçekleştirilmezse işlemlerde bekleme süreleri
	artabilmektedir. Bu yüzden bu şekilde derlenmesi gerekmektedir.</SPAN></FONT></FONT></P>
	<P CLASS="western" ALIGN=JUSTIFY STYLE="margin-bottom: 0in; line-height: 100%">
	<FONT COLOR="#c00000"><FONT SIZE=3><SPAN LANG="tr-TR">Tam olarak
	kaynağı main.c olan dosya için terminal ya da komut isteminden
	Codeblocks/Mingw/bin altındaki gcc.exe yoluna gidilerek aşağıdaki
	derleme komutu ile derlenmelidir.</SPAN></FONT></FONT></P>
	<P LANG="tr-TR" CLASS="western" ALIGN=JUSTIFY STYLE="margin-bottom: 0in; line-height: 100%">
	<BR>
	</P>
	<UL>
		<LI><P CLASS="western" ALIGN=JUSTIFY STYLE="text-indent: 0in; margin-bottom: 0in; line-height: 100%">
		<FONT COLOR="#ed7d31"><FONT SIZE=3><SPAN LANG="tr-TR">gcc -O3
		main.c -o “uygulamaismi”</SPAN></FONT></FONT></P>
	</UL>
	<P LANG="tr-TR" CLASS="western" ALIGN=JUSTIFY STYLE="margin-left: 0.7in; text-indent: 0in; margin-bottom: 0in; line-height: 100%">
	<BR>
	</P>
	<H1 LANG="en-US" CLASS="western">III.<FONT SIZE=3><B>GELİŞTİRME
	ORTAMI VE KULLANILAN DİL</B></FONT></H1>
	<P CLASS="western" ALIGN=JUSTIFY STYLE="text-indent: 0in; margin-bottom: 0in; line-height: 100%">
	      <FONT SIZE=3>Projeyi C programlama dilinde Windows işletim
	sistemi üzerinde gerçekleştirirken, geliştirme ortamı olarak
	gcc derleyicili Codeblocks 17.12 sürümünü kullandık. Programda
	kullandığımız kütüphaneler</FONT></P>
	<UL>
		<LI><P CLASS="western" ALIGN=JUSTIFY STYLE="text-indent: 0in; margin-bottom: 0in; line-height: 100%">
		<FONT SIZE=3>stdio.h</FONT></P>
		<LI><P CLASS="western" ALIGN=JUSTIFY STYLE="text-indent: 0in; margin-bottom: 0in; line-height: 100%">
		<FONT SIZE=3>stdlib.h</FONT></P>
		<LI><P CLASS="western" ALIGN=JUSTIFY STYLE="text-indent: 0in; margin-bottom: 0in; line-height: 100%">
		<FONT SIZE=3>dirent.h</FONT></P>
		<LI><P CLASS="western" ALIGN=JUSTIFY STYLE="text-indent: 0in; margin-bottom: 0in; line-height: 100%">
		<FONT SIZE=3>string.h</FONT></P>
		<LI><P CLASS="western" ALIGN=JUSTIFY STYLE="text-indent: 0in; margin-bottom: 0in; line-height: 100%">
		<FONT SIZE=3>math.h</FONT></P>
	</UL>
	<P LANG="tr-TR" CLASS="western" ALIGN=JUSTIFY STYLE="margin-bottom: 0in; line-height: 100%">
	<BR>
	</P>
	<H1 LANG="en-US" CLASS="western">IV.<FONT SIZE=3><B>DENEYSEL
	SONUÇLAR</B></FONT></H1>
	<P LANG="en-US" CLASS="western"><FONT SIZE=3><SPAN LANG="tr-TR">Bu
	projeyle birlikte büyük verilerle işlemler gerçekleştirmeye
	çalıştık ve bu verileri çeşitli işlemlerden geçirdik. Bu
	sırada geometri uygulamalarını daha yakından inceleme fırsatı
	bulduk. Elde ettiğimiz sonuçların doğruluğunu test etmek
	amacıyla verilerimizi görselleştirerek, kontrol edip bu
	modellerin çıktılarıyla kıyaslayarak kendi test yöntemlerimizi
	oluşturduk.En küçük küp problemini çözmeye çalışırken
	aslında bazı şartlar altında bir nokta kümesini kapsayan sonsuz
	sayıda küp olduğunu keşfettik.</SPAN></FONT></P>
	<H1 LANG="en-US" CLASS="western"><FONT SIZE=3><B>V.SONUÇ</B></FONT></H1>
	<P CLASS="western" ALIGN=JUSTIFY STYLE="margin-bottom: 0in; line-height: 100%">
	<FONT SIZE=3>Bu projenin gerçekleştirilmesiyle aslında çok fazla
	kazanım elde ettik. Bunlardan bahsetmemiz gerekirse geniş çaplı
	dosya işlemlerinde oldukça tecrübe elde ettik. C programlama
	dilinin güçlü bir yanı olan bellek işlemlerini bol bol kullanma
	fırsatı sağladık ve bu şekilde daha optimize bir program elde
	etmeye çalıştık. Kullanıcı deneyimini iyileştirmek için
	çalışmalar yapma fırsatı bulduk. Algoritma yeteneğimizi
	geliştirdik ve bir uygulamayı nasıl daha işlevsel hale
	getirebiliriz gibi sorularla ilgilendik.</FONT></P>
	<H1 LANG="en-US" CLASS="western"><FONT SIZE=3><B>VI.KAYNAKLAR</B></FONT></H1>
	<UL>
		<LI><P CLASS="western" ALIGN=CENTER STYLE="text-indent: 0in; margin-bottom: 0in; line-height: 100%">
		<FONT COLOR="#0000ff"><U><A HREF="https://publications.opengroup.org/"><FONT SIZE=3>https://publications.opengroup.org/</FONT></A></U></FONT></P>
		<LI><P CLASS="western" ALIGN=CENTER STYLE="text-indent: 0in; margin-bottom: 0in; line-height: 100%">
		<FONT COLOR="#0000ff"><U><A HREF="https://web.stanford.edu/class/archive/cs/cs107/cs107.1202/resources/gcc"><FONT SIZE=3>https://web.stanford.edu/class/archive/cs/cs107/cs107.1202/resources/gcc</FONT></A></U></FONT></P>
	</UL>
	<P LANG="en-US" CLASS="western" STYLE="text-indent: 0in"><BR><BR>
	</P>


</DIV>
<DIV ID="Section4" DIR="LTR">
	<P CLASS="western" ALIGN=CENTER STYLE="text-indent: 0in; margin-bottom: 0in; line-height: 100%">
	<FONT SIZE=4><B>Programın Genel Akış Şeması</B></FONT></P>
	<P CLASS="western" ALIGN=CENTER STYLE="text-indent: 0in; margin-bottom: 0in; line-height: 100%">
	<IMG SRC="http://burakcantemizel.com/resimler/3dn3.png" NAME="graphics4" ALIGN=BOTTOM WIDTH=674 HEIGHT=585 BORDER=0></P>
</DIV>
<DIV TYPE=FOOTER>
	<P ALIGN=CENTER STYLE="text-indent: 0in; margin-top: 0.46in; margin-bottom: 0in; line-height: 100%">
	<BR>
	</P>
</DIV>
</BODY>
</HTML>
