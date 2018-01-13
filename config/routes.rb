Rails.application.routes.draw do
  root 'main#landing'
  get 'gene' => 'main#gene'
end
