# 使用变分自动编码器进行半监督学习

主要介绍如何使用变分自动编码器进行半监督学习。  特别的会介绍在 “Semi-supervised Learning with Deep Generative Models” 这篇论文中用到的技术。 



## 半监督学习

半监督学习是一类尝试去使用无监督数据去进行监督学习的技术。 半监督学习在有监督学习和无监督学习之间，因为在其中可以同时使用有监督数据和无监督数据。

如果你有大量的无标注的数据。 你大多数情况下不会有一个基准的处理这些数据的准则。 比如说，在互联网上有着上千亿的图片，但是只有其中的一小部分是有着清楚的标注的。 所以我们的目标是使用大量的无标注数据获取最佳性能。

人类不知为何对这种工作非常擅长。 比如说大多数人没有肩见过食蚁兽，但是只要我们看过它的非常少的几张照片，就可以对其进行非常准确的分类。 我门对这个任务非常擅长是因为我们的大脑已经学习到了足够的共同特征，可以迅速对新的种类进行学习和分类。 对于机器来说，并没有什么不同，我们想要让机器通过无监督的学习到很多的基础特征来帮助真实的任务（只有少量的数据）。





## 变分自动编码器

首先介绍什么是变分自动编码器

### 自动编码器

自动编码机Auto-Encoder (AE)由两部分encoder和decoder组成，encoder输入x数据，输出潜在变量z，decoder输入z然后输出一个x’，目的是让x’与x的分布尽量一致，当两者完全一样时，中间的潜在变量z可以看作是x的一种压缩状态，包含了x的全部feature特征，此时监督信号就是原数据x本身。 

### 变分自动编码器

变分自动编码机VAE是自动编码机的一种扩展，它假设输出的潜在变量z服从一种先验分布，如高斯分布。这样，在训练完模型后，我们可以通过采样这种先验分布得到z’，这个z’可能是训练过程中没有出现过的，但是我们依然能在解码器中通过这个z’获得x’，从而得到一些符合原数据x分布的新样本，具有“生成“新样本的能力。

VAE是一种生成模型，它的目标是要得到 p(z|x) 分布，即给定输入数据 x 的分布，得到潜在变量 z 的分布， 与其他的生成模型一样，它计算的是x和z的联合概率分布p(x,z)（如朴素贝叶斯模型通过计算p(x,z)/p(x) 得到p(z∣x) ，当然它不是直接计算这个联合概率分布，而是借助一些公式变换求解。



前面讲过，变分自动编码机的目的是想知道观测数据x背后的潜在变量z分布，即p(z∣x) ，举个简单的例子，比如天气是我们的观测数据x，但我们想知道影响天气变化背后的一些无法观测的因素z，这个z就像自然法则一样能够左右最后观测到的天气，这样我们以后描述某个天气，就可以完全量化为对应的潜在变量z。对于这个例子，VAE/AE都能完成这个事情，但如果现在我们想生成一些新的天气样本来作为研究，这个时候只有VAE可以很容易做这个事情：拟合现有样本分布的一个潜在变量的先验分布，通过采样这个先验分布来获得新的样本；而对于AE这个事情就比较难了：由于每个样本x被固定编码为对应的z，我们无法知道潜在样本的分布（若此时我们知道了z的分布，就等于知道了真实数据x的分布，这显然是不可能的，相比VAE的解决方案是把真实数据x对应的潜在分布映射到一个先验分布上），若AE硬要获得新样本怎么做呢，此时只能随机采样z了，很显然我们无法验证：根据这个z是否能正确地还原出一个符合真实样本x的新样本。

除了单纯“生成“新的样本用途，生成模型还可以用来去噪声，比如现在的图片里有雾霾，我们想把图片里的雾霾去掉，还原没有雾霾的样子，就可以用VAE/AE做：把有雾霾的图片当作输入x，对应的无雾霾的图片（假设我们能够在天气好的时候获得）作为最后要还原的x’训练VAE模型，如果训练的足够好的话，以后再任意拿一张有雾霾的图片，VAE能够还原出这个图片没有雾霾的样子，这就是生成模型的优势。当然，判别模型也能做这个事情：在给定原图像的情况下，尽量拟合原图像的变换图像，但是若测试时出现了之前训练过程中没有出现的图像，效果会不好，因为判别模型是基于条件概率p(x′∣x) 若新的条件x模型都没见过，效果肯定不好啊，所以判别模型更注重泛化能力。而生成模型会去拟合x和x’联合概率分布p(x,x′) ，因此p(x′∣x)的计算只需要除以边缘概率分布p(x) p(x)p(x)即可，而对于VAE来说，它拟合的其实是x和潜在变量z的联合概率分布p(x,z)，获得p(z∣x) 从而间接生成x’。



VAEs 是一类重要的生成模型， 除了 VAEs 还有一类十分重要的模型 GANS。 



### VAE 数学推导

#### KL 散度

**相对熵**（relative entropy）又称为**KL散度**（**Kullback–Leibler divergence**，简称**KLD**），信息散度（information divergence），信息增益（information gain）。

**KL散度**是两个概率分布P和Q差别的非对称性的度量。 KL散度是用来 度量使用基于Q的编码来编码来自P的样本平均所需的额外的位元数。 典型情况下，P表示数据的真实分布，Q表示数据的理论分布，模型分布，或P的近似分布。

离散型随机变量，P和Q的概率分布 KL 散度

![](http://latex.codecogs.com/gif.latex?\\D_{kl}(P||Q)=-\sum_{i}P(x)ln\frac{Q(i)}{P(i)})

连续随机变量，可以按照积分的方式进行定义

![](http://latex.codecogs.com/gif.latex?\\D_{kl}(P||Q)=-\int_{-\infty}^{\infty}P(x)ln\frac{Q(i)}{P(i)}dx)

KL 的 散度的值是非负值，当且仅当 P = Q 时，KL 散度的值是0。

KL 并不是一个度量， 从 P 到 Q的距离通常不等于从Q到P的距离。



#### VAE 下界推导

为了求解真实的后验p(z∣x) p(z|x)p(z∣x)概率分布，VAE引入一个识别模型q(z∣x) q(z|x)q(z∣x)去近似p(z∣x) p(z|x)p(z∣x)，那么衡量这两个分布之间的差异自然就是相对墒了，也就是KL散度，VAE的目的就是要让这个相对墒越小，因此推导从相对墒开始：
$$
D_{kl}(q(z|x)||p(z|x))=-\int P(x)log\frac{q(z|x)}{p(z|x)}dz=E_{z\sim q(z|x)}log\frac{q(z|x)}{p(z,x)} + logP(x)
$$
![](http://latex.codecogs.com/gif.latex?\\D_{kl} q(z|x)||p(z|x)=-\int%20P(x)log\frac{q(z|x)}{p(z|x)}dz=E_{z\sim%20q(z|x)}log\frac{q(z|x)}{p(z,x)}%20+%20logP(x))

令上述期望项为  L(x), 可以明显的看出  L（x） <= logP(x)    因为 KL 散度的值是永远大于0的。

所以目标可以变为优化 L(x)

L(x) 经过贝叶斯展开和蒙特卡洛采样后，可以变成如下的形式

![](<http://latex.codecogs.com/gif.latex?\\L(x)=-KLq(z|x)||p(z|x)%20+%20E_{z\sim%20q(z|x)}logP(z,x)>)

![](<http://latex.codecogs.com/gif.latex?\\=\frac{1}{2}\sum_{j=1}^{J}1+log(\sigma_j^2)-\mu_j^2-\sigma_j^2%20+%20\frac{1}{L}\sum_{l=1}{L}logp(x|z_l)>)

其中 sigma 和 mu 是均值和方差， 后面的 zl 是蒙特卡罗采样的结果。  只要把这个作为一个损失函数进行处理即可。

#### python 代码实现

##### 1. 编码器

编码器的输出分两部分，一部分表示mean，一部分表示标准差std，其中由于标准差是恒大于0，因此用了softplus激活函数：

```python
def gaussian_MLP_encoder(...):
	# 1st hidden layer
	...
	
	# 2nd hidden layer
	...
	
	# output layer
	wo = tf.get_variable('wo', [h1.get_shape()[1], n_output * 2], initializer=w_init)
	bo = tf.get_variable('bo', [n_output * 2], initializer=b_init)
	gaussian_params = tf.matmul(h1, wo) + bo
	
	# The mean parameter is unconstrained
	mean = gaussian_params[:, :n_output]
	# The standard deviation must be positive. Parametrize with a softplus and
	# add a small epsilon for numerical stability
	stddev = 1e-6 + tf.nn.softplus(gaussian_params[:, n_output:])
```

##### 2. 解码器

输出的大小与输入一致，其中每个元素代表着此位置的像素值为0的概率(或者255，根据输入来定)，所以用sigmoid激活函数

```python
def bernoulli_MLP_decoder(...):
	# 1st hidden layer
	...
	
	# 2nd hidden layer
	w1 = tf.get_variable('w1', [h0.get_shape()[1], n_hidden], initializer=w_init)
	b1 = tf.get_variable('b1', [n_hidden], initializer=b_init)
	h1 = tf.matmul(h0, w1) + b1
	h1 = tf.nn.elu(h1)
	h1 = tf.nn.dropout(h1, keep_prob)
	
	# output layer-mean
	wo = tf.get_variable('wo', [h1.get_shape()[1], n_output], initializer=w_init)
	bo = tf.get_variable('bo', [n_output], initializer=b_init)
	y = tf.sigmoid(tf.matmul(h1, wo) + bo)
```

#### 3. 损失函数

```python
# 编码器得到标准差和均值向量
mu, sigma = gaussian_MLP_encoder(x_hat, n_hidden, dim_z, keep_prob)

# reparameterization 重参数采样得到z
z = mu + sigma * tf.random_normal(tf.shape(mu), 0, 1, dtype=tf.float32)

# 解码器传入z，输出y
y = bernoulli_MLP_decoder(z, n_hidden, dim_img, keep_prob)
y = tf.clip_by_value(y, 1e-8, 1 - 1e-8)

# marginal_likelihood loss为y与输入数据x之间交叉墒，即解码器的损失
marginal_likelihood = tf.reduce_sum(x * tf.log(y) + (1 - x) * tf.log(1 - y), 1)
marginal_likelihood = tf.reduce_mean(marginal_likelihood)

# KL_divergence为z与标准高斯分布之间的差距，即编码器的损失
KL_divergence = 0.5 * tf.reduce_sum(tf.square(mu) + tf.square(sigma) - tf.log(1e-8 + tf.square(sigma)) - 1, 1)
KL_divergence = tf.reduce_mean(KL_divergence)

# 变分下界L(x)，目标最大化
ELBO = marginal_likelihood - KL_divergence

# 令损失函数为-L(x)，目标梯度下降最小化
loss = -ELBO
```



## VAE 进行半监督学习

由于上述VAE的特性，因为VAE可以自己产生新的数据

所以使用VAE进行半监督学习的方法的思路可以简单的理解为： 先训练一个VAE， 然后利用VAE对所有的未标注数据产生标注数据。 产生了全部标注标注数据后进行正常的监督学习的训练过程。

1. Train a VAE using *all* our data points (labelled and unlabelled), and transform our observed data (XX) into the latent space defined by the ZZ variables.
2. Solve a standard supervised learning problem on the *labelled* data using (Z,Y)(Z,Y) pairs (where YY is our label).